//
// Created by wrc on 22-12-14.
//

// You may need to build the project (run Qt uic code generator) to get "ui_face_detect.h" resolved

#include "face_detect.h"
#include "ui_face_detect.h"
#include <fstream>


face_detect::face_detect(QWidget *parent) :
        QDialog(parent), ui(new Ui::face_detect) {

    ui->setupUi(this);

    // 界面的初始化   默认选中 本地相机和离线检测
//    ui->local_radioButton->setChecked(true);
    ui->astra_radioButton->setChecked(true);
//    ui->offline_radioButton->setChecked(true);
    ui->feature_radioButton->setChecked(true);

    ui->main_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->main_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene();
    face = new ArcFace();
    m_timer = new QTimer();
    m_thread = new QThread();
    m_view = new graphics_view();
    m_view->moveToThread(m_thread);

    // TODO 相机突然断开连接后处理，astra系列相机搞得有点麻烦
    connect(m_view, &graphics_view::link_error, [=] {
        scene->clear();
        cam->close();
        m_timer->stop();
        m_thread->quit();
        m_thread->wait();
        choose_cam_radio_btn_enable(true);
        showMessageBox(this, "相机断开连接!");
        return;
    });

    // 避免放大缩小graphics_view的的时候画面重叠
    connect(scene, &QGraphicsScene::sceneRectChanged, [=] {
        scene->clear();
    });

    // 定时器的信号与槽
    connect(m_timer, &QTimer::timeout, m_view, &graphics_view::time_out_slot, Qt::DirectConnection);

    connect(m_view, &graphics_view::get_frame, [=](cv::Mat m) {

        if (ui->offline_radioButton->isChecked()) {
            // 离线 -- (离线不查数据库，只显示基本人物属性)
            auto offline_res = face->detect(m, false, VIDEO);
            m = offline_res.detect_image;
        } else if (ui->live_radioButton->isChecked()) {
            // 活体
            std::cout << "活体未开发..." << std::endl;
        } else if (ui->feature_radioButton->isChecked()) {
            // 特征 -- (查询数据库，与数据库中特征进行比对，与离线相比会多输出用户信息)  todo
            auto online_res = face->detect(m, true, VIDEO, local_feature);
            m = online_res.detect_image;
        }
        showImage(m);
    });

    connect(this, &face_detect::online_signal, [=](bool f) {
        if (f) {
            ui->offline_det_btn->setEnabled(false);
        } else {
            ui->offline_det_btn->setEnabled(true);
        }
    });

    // 在线检测
    connect(ui->online_det_btn, &QPushButton::clicked, [=] {
        this->is_online = !this->is_online;
        emit
        this->online_signal(is_online);
        if (is_online) {
            qDebug("在线检测ON");
            std::string cam_name;
            if (ui->local_radioButton->isChecked()) {
                cam = new local_camera();
                cam_name = "本地相机";
            } else if (ui->astra_radioButton->isChecked()) {
                cam_name = "乐视三合一相机";
                cam = new AstraCamera();
            } else {
                throw runtime_error("未定义的相机型号...");
            }

            if (!cam->checkOpen()) {
                std::string title = cam_name + "打开失败,请检查是否接线正常!";
                showMessageBox(this, title.data());
                this->is_online = !this->is_online;
                return;
            }

            cam->start(SteamMode::RGB);
            m_view->set_cam(cam);
            m_thread->start();
            m_timer->start();
            ui->online_det_btn->setText("在线检测-关闭");
            choose_cam_radio_btn_enable(false);
            ui->online_det_btn->setStyleSheet("background-color: rgb(120, 0, 0);color: white");
        } else {
            qDebug("在线检测OFF");
            cam->close();
            m_timer->stop();
            m_thread->quit();
            m_thread->wait();
            scene->clear();
            ui->online_det_btn->setText("在线检测-开启");
            choose_cam_radio_btn_enable(true);
            ui->online_det_btn->setStyleSheet("");
        }
    });

    // TODO rn 离线检测
    connect(ui->offline_det_btn, &QPushButton::clicked, [=] {
        qDebug("离线检测");
        QString path = QFileDialog::getOpenFileName(this,
                                                    "请选择一张检测图片",
                                                    ".",
                                                    tr("Image Files(*.png *.jpg)"));
        if (path.isEmpty()) {
            qDebug("未选择退出.");
            return;
        }

        auto m = cv::imread(path.toStdString());
        std::pair<string, ASF_FaceFeature> name_feature;
        vector<std::pair<string, ASF_FaceFeature>> features;
        // 遍历数据库，生成结构体
        QSqlQuery query;
        QString sql = "select UserName,FeatureSize,Feature from features";
        if (query.exec(sql)) {
            //循环取出所有查询结果,对应结果是QVariant类型可以自行to到其他类型
            while (query.next()) {
                name_feature.first = query.value(0).toString().toStdString();
                name_feature.second.featureSize = query.value(1).toInt();
                // todo feature 写到本地
                auto a = query.value(2).toByteArray();
                auto b = (a.cbegin(), a.cend());
                auto *p = (unsigned char *) b[0];

                name_feature.second.feature = p;

                features.emplace_back(name_feature);

            }
        }
        auto res = face->detect(m, true, IMAGE, features);
        showImage(res.detect_image);
        if (!res.flag) {
            showMessageBox(this, "数据库中未保存当前人脸特征,请注册再试!");
        }
        qDebug("离线检测完成");
    });

    // todo 离线注册
    connect(ui->offline_reg_btn, &QPushButton::clicked, [=] {
        qDebug("离线注册");
        QString path = QFileDialog::getOpenFileName(this,
                                                    "请选择一张待注册图片",
                                                    ".",
                                                    tr("Image Files(*.png *.jpg)"));
        if (path.isEmpty()) {
            qDebug("未选择退出.");
            return;
        }
        auto res = face->face_features_extract(cv::imread(path.toStdString()));
        bool f;
        ASF_FaceFeature feature;
        string msg;
        cv::Mat rm;

        std::tie(f, feature, msg, rm) = res;

        if (f) {
            qDebug("特征提取成功");
            showImage(rm);
            auto result = showInputBox(this, "特征提取成功", "用户名");
            if (!result.first) {
                qDebug("未输入用户名");
            } else {
                // todo 后需要做 检查该特征是否保存在数据库中.检查名字和特征。分为两个提示用户。
                QSqlQuery query;
                QString sql = "insert into features(UserName,FeatureSize,Feature) values (:UserName,:FeatureSize,:Feature)";
                query.prepare(sql);
                query.bindValue(":UserName", result.second.data());
                query.bindValue(":FeatureSize", feature.featureSize);
                // todo feature写到数据库中
                auto feature_byte = QByteArray(reinterpret_cast<const char *>(&feature.feature), feature.featureSize);
                query.bindValue(":Feature", feature_byte);

                if (!query.exec()) {
                    qDebug("insert fail");

                }
                query.clear();

            }
            scene->clear();
        } else {
            qDebug("特征提取失败");
            showMessageBox(this, ("特征提取失败!\n失败原因:[" + msg + "]").data());
            return;
        }
        if (ui->comboBox->isEnabled()) {
            show_database();
        }
    });


    // 管理员登录
    connect(ui->admin_btn, &QPushButton::clicked, [=] {
        is_login = !is_login;
        if (is_login) {
            std::string pass_word = ui->lineEdit->text().toStdString();
            // 默认密码 123
            if (pass_word != "123") {
                showMessageBox(this, "密码错误!");
                ui->lineEdit->clear();
                is_login = !is_login;
                return;
            }

            ui->groupBox_2->setEnabled(true);
            ui->lineEdit->clear();

            // todo 人脸数据库更新
            this->show_database();

            ui->lineEdit->setEnabled(false);
            ui->admin_btn->setText("管理员退出");
            ui->admin_btn->setStyleSheet("background-color: rgb(120, 0, 0);color: white");
        } else {
            ui->lineEdit->setEnabled(true);
            ui->groupBox_2->setEnabled(false);
            ui->comboBox->clear();
            ui->num_label->clear();
            ui->admin_btn->setText("管理员登录");
            ui->admin_btn->setStyleSheet("");
        }
    });

    // 删除人脸信息
    connect(ui->del_btn, &QPushButton::clicked, [=] {
        qDebug("删除");
        auto cur_text = ui->comboBox->currentText();
        QSqlQuery query;
        QString sql = "delete from features where UserName=:CurName";
        query.prepare(sql);
        query.bindValue(":CurName", cur_text);
        // todo 删除警告?
        if (!query.exec()) {
            throw runtime_error("选中的用户名不存在于数据库中，却显示在界面上!");
        }
        show_database();
    });

    // 更名
    connect(ui->rename_btn, &QPushButton::clicked, [=] {
        qDebug("更名");
        auto cur_text = ui->comboBox->currentText();

        QSqlQuery query;
        while (true) {
            string label = "将 " + cur_text.toStdString() + " 更改为 ";
            auto res = showInputBox(this, "更名", label.data());
            if (!res.first) {
                showMessageBox(this, "更名已撤销");
                break;
            }
            auto change_name = res.second;
            if (change_name.empty()) {
                showMessageBox(this, "不能使用空字符串作为新的命名!");
                continue;
            }
            QString sql = "update features set UserName=:ChangeName where UserName=:CurName";
            query.prepare(sql);
            query.bindValue(":CurName", cur_text);
            query.bindValue(":ChangeName", QString(change_name.data()));
            if (!query.exec()) {
                std::cout << "啥玩意就sql语句更名失败了啊" << std::endl;
            }
            break;
        }
        show_database();
    });

    // 初始化数据库
    init_database();
}

face_detect::~face_detect() {
    cout << "xxx face detect" << endl;
    scene->deleteLater();
    delete cam;
    delete face;
    m_timer->stop();
    m_timer->deleteLater();
    m_thread->quit();
    m_thread->wait();
    m_view->deleteLater();
    database.close();
    delete ui;
}

void face_detect::closeEvent(QCloseEvent *e) {
    cout << "点击关闭按钮" << endl;
    scene->clear();
}

inline void face_detect::showImage(cv::Mat &frame) {
    // ----注意:每次update scene之前必须clear掉上一帧，否则会造成持续帧的累计，内存占用过大!----
    scene->clear();
    // ------------------------------------------------------------------------------
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage q_img((const unsigned char *) frame.data, frame.cols, frame.rows, frame.step,
                 QImage::Format_RGB888);
    auto iw = q_img.width();
    auto ih = q_img.height();
    auto gw = ui->main_graphicsView->width();
    auto gh = ui->main_graphicsView->height();
    auto diffx = gw - iw;
    auto diffy = gh - ih;
    double scale;
    if (diffx > diffy) {
        // y方向小
        scale = (double) gh / (double) ih;
    } else {
        scale = (double) gw / (double) iw;
    }
    // scene xy指的是显示的图像中心
    scene->setSceneRect(0, 0, (int) (iw * scale), (int) (ih * scale));
    q_img = q_img.scaled((int) (iw * scale), (int) (ih * scale), Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation);
    scene->addPixmap(QPixmap::fromImage(q_img));
    ui->main_graphicsView->setScene(scene);
}

void face_detect::show_database() {
    ui->comboBox->clear();
    QSqlQuery query;
    int c = 0;
    QString sql = "select UserName,FeatureSize,Feature from features";
    if (query.exec(sql)) {
        while (query.next()) {
            ui->comboBox->addItem(query.value(0).toString());
            c += 1;
        }
    }
    ui->num_label->setText(QString(to_string(c).data()));
}

void face_detect::choose_cam_radio_btn_enable(bool f) {
    ui->local_radioButton->setEnabled(f);
    ui->astra_radioButton->setEnabled(f);
}

void face_detect::init_database() {
    qDebug("初始化数据库");
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        database = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("FaceFeatures.db");
        database.setUserName("facefeatures");
        database.setPassword("123");
    }

    if (!database.open()) {
        showMessageBox(this, "数据库连接异常!");
    } else {

        QSqlQuery query;
        // 查看表是否创建，未创建自动创建
        QString sql = "create table if not exists features(UserName TEXT PRIMARY KEY, FeatureSize INTEGER, Feature BLOB)";
//        QString sql = "create table if not exists features(UserName TEXT PRIMARY KEY, FeatureSize INTEGER, Feature TEXT)";
        query.exec(sql);
        if (!query.exec(sql)) {
            qDebug("sql语句执行失败,创建features表不成功!");
        }
        query.clear();

        // todo 将数据库中的特征全部加入到内存中，用于特征比对
//        vector<std::pair<string, ASF_FaceFeature>> features
        std::pair<string, ASF_FaceFeature> name_feature;
//        vector<std::pair<string, ASF_FaceFeature>> features;
        // 遍历数据库，生成结构体
        sql = "select UserName,FeatureSize,Feature from features";
        if (query.exec(sql)) {
            //循环取出所有查询结果,对应结果是QVariant类型可以自行to到其他类型
            while (query.next()) {
                name_feature.first = query.value(0).toString().toStdString();
                name_feature.second.featureSize = query.value(1).toInt();

                char p[name_feature.second.featureSize];
                auto a = query.value(2).toByteArray();
                a.resize(sizeof(p));
                memcpy(a.data(), p, sizeof(p));
                unsigned char *buf = reinterpret_cast<unsigned char *>(p);

//                auto b=a.data();
//                unsigned char *buf= reinterpret_cast<unsigned char *>(b);
//                char p[name_feature.second.featureSize];
//                int len_arr = a.size();
//                int len_b = sizeof(p);
//                int len = qMin(len_arr, len_b);
//                memcpy(p, a, len);
//                unsigned char *buf = reinterpret_cast<unsigned char *>(p);
//                name_feature.second.feature = buf;



//                auto b = a.data();
////                QByteArray b = a.toString().toLatin1();
//                auto *kkk = reinterpret_cast<unsigned char *>(b);
////                auto *k = reinterpret_cast<unsigned char *>(a.data());
////                unsigned char *uc_feature2;
////                unsigned char *uc_feature = (unsigned char *) (query.value(2).toString().toStdString()).data();
////                uc_feature2 = uc_feature;
//                name_feature.second.feature = kkk;
////                unsigned char *uc_feature = reinterpret_cast<unsigned char *>(query.value(2).toString().data());

                name_feature.second.feature = buf;
                local_feature.push_back(name_feature);
            }
        }

        qDebug("数据库导入完成!");

        // 删除
//        "delete from StuInfo where num=%1"
//        sql = "delete from features where UserName='wuyanzhu'";
//        query.exec(sql);
//        query.clear();

        // 增加
//        insert into StuInfo(num,name,age,score) values (%1,'%2',%3,%4).arg(...
//        sql = "insert into features(UserName,FeatureSize,Feature) values ('wuyanzhu','123','888')";
//        if (query.exec(sql)) {
//            qDebug("insert ok");
//        }
//        query.clear();
//        QString sql = "select UserName,UserPwd from UserInfo";

//         查询
//        sql = "select UserName,FeatureSize,Feature from features";
//        if (query.exec(sql)) {
//            //循环取出所有查询结果,对应结果是QVariant类型可以自行to到其他类型
//            while (query.next()) {
//                qDebug() << query.value(0).toString() << query.value(1).toInt() << query.value(2).toString();
////                query.value(2).toDate();
////                unsigned char *m_data = (unsigned char *)query.value(2).toString().toStdString().c_str();
////                std::cout<<m_data<<std::endl;
////                unsigned char *m_data = (unsigned char *)query.value(2).toString().data();
////                    string a="123";
////                    a.c_str();
////                const unsigned char *s = static_cast<const unsigned char *> ( query.value(2).toString().c_str());
//            }
//        }

//        if (query.exec(sql)) {
//            qDebug("check ok");
//        }
//        QString sql = "create table features (Name varchar(100) primary key, FeatureSize varchar(30), Feature int)";


    }
}

void graphics_view::set_cam(BaseCamera *_cam) {
    this->cam = _cam;
}

void graphics_view::time_out_slot() {
//    if (!cam->checkOpen()) {
//        throw runtime_error("link error");
//        std::cout << "send link error1" << std::endl;
//        emit this->link_error();
//        std::cout << "send link error2" << std::endl;
//        return;
//    }
    this->cam->updateFrame();
    auto mat = this->cam->getColorMat();
    emit
    this->get_frame(mat);
}

graphics_view::graphics_view(QObject *parent) : QObject(parent) {

}

graphics_view::~graphics_view() {

}
