//
// Created by wrc on 22-12-8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_temple_match.h" resolved

#include <fstream>
#include "temple_match.h"
#include "ui_temple_match.h"


class Timer {
public:
    Timer() : beg_(clock_::now()) {}

    void reset() { beg_ = clock_::now(); }

    double elapsed() const {
        return std::chrono::duration_cast<second_>
                (clock_::now() - beg_).count();
    }

    void out(std::string message = "") {
        double t = elapsed();
        std::cout << message << "\nelasped time:" << t << "s" << std::endl;
        reset();
    }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};


namespace cv_dnn {
    namespace {

        template<typename T>
        static inline bool SortScorePairDescend(const std::pair<float, T> &pair1,
                                                const std::pair<float, T> &pair2) {
            return pair1.first > pair2.first;
        }

    } // namespace

    inline void GetMaxScoreIndex(const std::vector<float> &scores, const float threshold, const int top_k,
                                 std::vector<std::pair<float, int> > &score_index_vec) {
        for (size_t i = 0; i < scores.size(); ++i) {
            if (scores[i] > threshold) {
                score_index_vec.push_back(std::make_pair(scores[i], i));
            }
        }
        std::stable_sort(score_index_vec.begin(), score_index_vec.end(),
                         SortScorePairDescend<int>);
        if (top_k > 0 && top_k < (int) score_index_vec.size()) {
            score_index_vec.resize(top_k);
        }
    }

    template<typename BoxType>
    inline void NMSFast_(const std::vector<BoxType> &bboxes,
                         const std::vector<float> &scores, const float score_threshold,
                         const float nms_threshold, const float eta, const int top_k,
                         std::vector<int> &indices, float (*computeOverlap)(const BoxType &, const BoxType &)) {
        CV_Assert(bboxes.size() == scores.size());
        std::vector<std::pair<float, int> > score_index_vec;
        GetMaxScoreIndex(scores, score_threshold, top_k, score_index_vec);

        // Do nms.
        float adaptive_threshold = nms_threshold;
        indices.clear();
        for (size_t i = 0; i < score_index_vec.size(); ++i) {
            const int idx = score_index_vec[i].second;
            bool keep = true;
            for (int k = 0; k < (int) indices.size() && keep; ++k) {
                const int kept_idx = indices[k];
                float overlap = computeOverlap(bboxes[idx], bboxes[kept_idx]);
                keep = overlap <= adaptive_threshold;
            }
            if (keep)
                indices.push_back(idx);
            if (keep && eta < 1 && adaptive_threshold > 0.5) {
                adaptive_threshold *= eta;
            }
        }
    }


// copied from opencv 3.4, not exist in 3.0
    template<typename _Tp>
    static inline
    double jaccardDistance__(const Rect_<_Tp> &a, const Rect_<_Tp> &b) {
        _Tp Aa = a.area();
        _Tp Ab = b.area();

        if ((Aa + Ab) <= std::numeric_limits<_Tp>::epsilon()) {
            // jaccard_index = 1 -> distance = 0
            return 0.0;
        }

        double Aab = (a & b).area();
        // distance = 1 - jaccard_index
        return 1.0 - Aab / (Aa + Ab - Aab);
    }

    template<typename T>
    static inline float rectOverlap(const T &a, const T &b) {
        return 1.f - static_cast<float>(jaccardDistance__(a, b));
    }

    void NMSBoxes(const std::vector<Rect> &bboxes, const std::vector<float> &scores,
                  const float score_threshold, const float nms_threshold,
                  std::vector<int> &indices, const float eta = 1, const int top_k = 0) {
        NMSFast_(bboxes, scores, score_threshold, nms_threshold, eta, top_k, indices, rectOverlap);
    }

}

temple_match::temple_match(QWidget *parent) :
        QDialog(parent), ui(new Ui::temple_match) {
    ui->setupUi(this);

    m_Image = new ImageWidget(ui->graphicsView);

    // graphics view隐藏滚动栏
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_Image_temp = new ImageWidget(ui->graphicsViewTemplate);//实例化类ImageWidget的对象m_Image，该类继承自QGraphicsItem，是自己写的类
    // graphics view隐藏滚动栏
    ui->graphicsViewTemplate->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewTemplate->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    initUpdateInfo();

    // 鼠标点击更新combox
    ui->comboBox->installEventFilter(this);

    connect(ui->pushButtonChoose, &QPushButton::clicked, this, &temple_match::clickChooseBtn);
    connect(ui->pushButtonTrain, &QPushButton::clicked, this, &temple_match::clickTrainBtn);
    connect(ui->pushButtonDet, &QPushButton::clicked, this, &temple_match::clickDetBtn);
    // 根据combox的选择更新temp show的视窗
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &temple_match::changeComBoxChoose);
}

temple_match::~temple_match() {
    ofstream fout(cfg_path);
    config["last_template"] = ui->comboBox->currentText().toStdString();
    cout << "cfg写入完成" << endl;
    fout << config;
    fout.close();

    delete m_Image;
    delete m_Image_temp;
    delete ui;
    cout << "xxx temple match ui" << endl;
}

void temple_match::clickChooseBtn() {
    qDebug("点击选择文件按钮");
    string file_path = QFileDialog::getOpenFileName(this, "选择图片", "/home/wrc/Downloads/test",
                                                    "image(*.png *.jpg *.bmp)").toStdString();
    if (file_path.empty()) {
        qDebug("未选择图片路径");
        return;
    }
    chooseFilePath = file_path;
    auto image = QImage(file_path.data());
//    graphicsViewShow(image);
    m_Image->graphics(image, file_path);
}

void temple_match::clickTrainBtn() {
    qDebug("点击训练按钮");
    if (chooseFilePath.empty()) {
        showMessageBox(this, "请选择一张图片并进行标注,再执行训练!");
        return;
    }
    if (!m_Image->hasRoiRect()) {
        showMessageBox(this, "请先进行标注,再执行训练!\n提示:双击鼠标左键,可打开框选工具!");
        return;
    }
    Mat c_mat = m_Image->getRoiRectToMat();
//    imwrite("./debug.png", c_mat);
    if (c_mat.empty()) {
        imwrite("./什么玩意(c_mat.empty).png", c_mat);
        throw runtime_error("获取到的mat为空!");
    }
    // train
    // first:info second:Mat
    auto feature_num = ui->lineEditFutrueNum->text().toFloat();
    auto weak = ui->lineEditWeak->text().toFloat();
    auto strong = ui->lineEditStrong->text().toFloat();
    auto rotation_step = ui->lineEditRotationStep->text().toFloat();
    auto scale_step = ui->lineEditScaleStep->text().toFloat();

    auto rotation_range = splitStringToFloat(ui->lineEditRotationRange->text().toStdString());
    auto scale_range = splitStringToFloat(ui->lineEditScaleRange->text().toStdString());

    auto depth_range = splitStringToInt(ui->lineEditDepth->text().toStdString());

    line2Dup::Detector detector(feature_num, depth_range, weak, strong);

    assert(!c_mat.empty() && "check your img path");
    Mat mask = Mat(c_mat.size(), CV_8UC1, {255});

    shape_based_matching::shapeInfo_producer shapes(c_mat, mask);
    shapes.angle_range = rotation_range;
    shapes.angle_step = rotation_step;

    shapes.scale_range = scale_range;
    shapes.scale_step = scale_step;

    shapes.produce_infos();

    std::vector<shape_based_matching::shapeInfo_producer::Info> infos_have_templ;
    string class_id = "test";
    int templ_id = 0;
    Mat to_show;
    for (auto &info: shapes.infos) {
        to_show = shapes.src_of(info);

        std::cout << "\ninfo.angle: " << info.angle << std::endl;
        templ_id = detector.addTemplate(shapes.src_of(info), class_id, shapes.mask_of(info),
                                        int(feature_num * info.scale));
        std::cout << "templ_id: " << templ_id << std::endl;

        auto templ = detector.getTemplates("test", templ_id);
        for (int i = 0; i < templ[0].features.size(); i++) {
            auto feat = templ[0].features[i];
            cv::circle(to_show, {feat.x + templ[0].tl_x, feat.y + templ[0].tl_y}, 3, {0, 0, 255}, -1);
        }

        if (templ_id != -1) {
            infos_have_templ.push_back(info);
        }
    }

    m_Image->graphicsImageFromMat(to_show);

    cout << "train successful!" << endl;

    auto res = showInputBox(this, "训练完成", "模板文件名:");
    if (!res.first) {
        showMessageBox(this, "取消保存");
        return;
    }
    string save_root_dir{};
    while (true) {
        if (res.second.empty()) {
            showMessageBox(this, "输入的模板文件名不能为空!");
        } else {
            save_root_dir = path + res.second + "/";
            string cmd = "mkdir -p " + save_root_dir;
            system(cmd.data());
            detector.writeClasses(save_root_dir + "train.yaml");
            shapes.save_infos(infos_have_templ, save_root_dir + "train_info.yaml");
            imwrite(save_root_dir + "template.png", to_show);
            showMessageBox(this, ("保存模板[" + res.second + "]完成").data());
            break;
        }
    }

    ui->comboBox->addItem(res.second.data());
    ui->comboBox->setCurrentText(res.second.data());
    auto q = QImage((save_root_dir + "template.png").data());
//    m_Image_temp->graphics(q, save_root_dir + "template.png");
}

void temple_match::clickDetBtn() {
    qDebug("点击匹配按钮");
//    if (m_Image.)
    auto c_mat = m_Image->getScenceToMat();
    if (c_mat.empty()) {
        showMessageBox(this, "未设置需要匹配的图片!");
        return;
    }

    if (ui->comboBox->currentText().isEmpty()) {
        showMessageBox(this, "注册列表为空!");
        return;
    }

    string cur_path = path + ui->comboBox->currentText().toStdString();

    auto th = ui->lineEdithreshold->text().toFloat();
    auto path1 = cur_path + "/train.yaml";
    auto path2 = cur_path + "/train_info.yaml";

    auto feature_num = ui->lineEditFutrueNum->text().toFloat();
    auto weak = ui->lineEditWeak->text().toFloat();
    auto strong = ui->lineEditStrong->text().toFloat();
    auto nms_th = ui->lineEditNMS->text().toFloat();
    auto tp_name = ui->comboBox->currentText().toStdString();
    auto depth_range = splitStringToInt(ui->lineEditDepth->text().toStdString());

    line2Dup::Detector detector(feature_num, depth_range, weak, strong);
    std::vector<std::string> ids;
    ids.push_back("test");


    detector.readClasses(ids, path1);

    auto infos = shape_based_matching::shapeInfo_producer::load_infos(path2);

    assert(!c_mat.empty() && "check your img");

    // cvtColor(test_img, test_img, CV_BGR2GRAY);

    int stride = 16;
//    int stride = 8;
    int n = c_mat.rows / stride;
    int m = c_mat.cols / stride;
    Rect roi(0, 0, stride * m, stride * n);

    c_mat = c_mat(roi).clone();

    Timer timer;
    auto matches = detector.match(c_mat, th, ids);
    timer.out();

    std::cout << "matches.size(): " << matches.size() << std::endl;
    size_t top5 = 500;
//    if (top5 > matches.size()) top5 = matches.size();
    if (top5 > matches.size()) top5 = matches.size();

    vector<Rect> boxes;
    vector<float> scores;
    vector<int> idxs;
    for (auto match: matches) {
        Rect box;
        box.x = match.x;
        box.y = match.y;

        auto templ = detector.getTemplates("test",
                                           match.template_id);

        box.width = templ[0].width;
        box.height = templ[0].height;
        boxes.push_back(box);
        scores.push_back(match.similarity);
    }

    cv_dnn::NMSBoxes(boxes, scores, th, nms_th, idxs);

    for (auto idx: idxs) {
        auto match = matches[idx];
        auto templ = detector.getTemplates("test",
                                           match.template_id);

//        cout << "angle:" << endl;
//        cout << infos[match.template_id].angle << endl;
//        cout << "scale:" << endl;
//        cout << infos[match.template_id].scale << endl;

//        int x = templ[0].width + match.x;
//        int y = templ[0].height + match.y;
        int r = templ[0].width / 2;
        cv::Vec3b Color{0, 255, 0};
//        cv::Vec3b randColor;
//        randColor[0] = rand() % 155 + 100;
//        randColor[1] = rand() % 155 + 100;
//        randColor[2] = rand() % 155 + 100;
        int theta = 2;
        for (int i = 0; i < templ[0].features.size(); i++) {
            auto feat = templ[0].features[i];
            cv::line(c_mat, {feat.x + match.x, feat.y + match.y + theta}, {feat.x + match.x, feat.y + match.y - theta},
                     Color);
            cv::line(c_mat, {feat.x + match.x - theta, feat.y + match.y}, {feat.x + match.x + theta, feat.y + match.y},
                     Color);
        }

        cv::putText(c_mat,
                    to_string(int(round(match.similarity))) + "-" +
                    to_string(int(round(infos[match.template_id].angle))) + "-" +
                    to_string(int(round(infos[match.template_id].scale))),
                    Point(match.x + r - 30, match.y - 3), FONT_HERSHEY_PLAIN, 2, Color);
//        cv::rectangle(c_mat, {match.x, match.y}, {x, y}, randColor, 2);

        std::cout << "\nmatch.template_id: " << match.template_id << std::endl;
        std::cout << "match.similarity: " << match.similarity << std::endl;
    }

//    imshow("img", c_mat);
//    waitKey(0);
    m_Image->graphicsImageFromMat(c_mat);

    std::cout << "test end" << std::endl << std::endl;

}

bool temple_match::eventFilter(QObject *watched, QEvent *event) {

    if (event->type() == QEvent::MouseButtonPress) {
        if (watched == ui->comboBox) {
            QComboBox *comboBox = qobject_cast<QComboBox *>(watched);

            comboBox->clear();

            // 通过读取datas下目录更新combox选项
            DIR *dir = opendir(path.c_str());
            struct dirent *entry;
            while ((entry = readdir(dir)) != nullptr) {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                    continue;
                }
//                std::cout << entry->d_name << std::endl;
                ui->comboBox->addItem(entry->d_name);
            }
            closedir(dir);
        }
    }
    return QDialog::eventFilter(watched, event);
}

void temple_match::initUpdateInfo() {
// 初始化时更新一下combox选项
    config = YAML::LoadFile(cfg_path);
    string last_template = config["last_template"].as<std::string>();
    if (!last_template.empty()) {
//        cout << "上次加载模板为:" << last_template << endl;
        ui->comboBox->addItem(last_template.data());
        ui->comboBox->setCurrentText(last_template.data());
        string save_root_dir = path + last_template + "/";
        try {
            auto q = QImage((save_root_dir + "template.png").data());
            m_Image_temp->graphics(q, save_root_dir + "template.png");
//            m_Image_temp->setScale(0.26738);
//            cout<<"scale value:"<<endl;
//            cout << m_Image_temp->getScaleValue()
//                 << endl;
        }
        catch (exception) {
            qDebug("删除啦？");
        }
    }
}

void temple_match::changeComBoxChoose() {
    cout << "update combox text!" << endl;
    auto name = ui->comboBox->currentText().toStdString();
    auto img_path = path + name + "/template.png";
    cout << img_path << endl;
    auto q = QImage(img_path.data());
    m_Image_temp->graphics(q, img_path);
}
