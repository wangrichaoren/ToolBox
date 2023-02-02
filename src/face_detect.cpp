//
// Created by wrc on 22-12-14.
//

// You may need to build the project (run Qt uic code generator) to get "ui_face_detect.h" resolved

#include "face_detect.h"
#include "ui_face_detect.h"


face_detect::face_detect(QWidget *parent) :
        QDialog(parent), ui(new Ui::face_detect) {

    ui->setupUi(this);

    // 界面的初始化   默认选中 本地相机和离线检测
    ui->local_radioButton->setChecked(true);
    ui->offline_radioButton->setChecked(true);

    ui->main_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->main_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene();
    face = new ArcFace();
    m_timer = new QTimer();
    m_thread = new QThread();
    m_view = new graphics_view();
    m_view->moveToThread(m_thread);

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

    // 定时器的信号与槽
    connect(m_timer, &QTimer::timeout, m_view, &graphics_view::time_out_slot, Qt::DirectConnection);

    connect(m_view, &graphics_view::get_frame, [=](cv::Mat m) {

        if (ui->offline_radioButton->isChecked()) {
            // 离线
            m = face->detect(m);
        } else if (ui->live_radioButton->isChecked()) {
            // 活体
            std::cout << "活体未开发..." << std::endl;
        } else if (ui->feature_radioButton->isChecked()) {
            // 特征
            std::cout << "特征" << std::endl;
        }
        showImage(m);
    });


    // 在线检测
    connect(ui->online_det_btn, &QPushButton::clicked, [=] {
        this->is_online = !this->is_online;
        if (is_online) {
            std::cout << "打开在线检测" << std::endl;
            std::string cam_name;
            if (ui->local_radioButton->isChecked()) {
                std::cout << "打开本地相机" << std::endl;
                cam = new local_camera();
                cam_name = "本地相机";
            } else if (ui->astra_radioButton->isChecked()) {
                std::cout << "打开乐视三合一相机" << std::endl;
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
            ui->online_det_btn->setText("在线检测(ON)");
            choose_cam_radio_btn_enable(false);
        } else {
            std::cout << "关闭在线检测" << std::endl;
            cam->close();
            m_timer->stop();
            m_thread->quit();
            m_thread->wait();
            scene->clear();
            ui->online_det_btn->setText("在线检测(OFF)");
            choose_cam_radio_btn_enable(true);
        }

    });

    // 管理员登录
    connect(ui->admin_btn, &QPushButton::clicked, [=] {
        std::string pass_word = ui->lineEdit->text().toStdString();
        // 默认密码 123
        if (pass_word != "123") {
            showMessageBox(this, "密码错误!");
            return;
        }
        ui->groupBox_2->setEnabled(true);
        // init database and set
        this->init_database();
    });


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
    delete ui;
}

void face_detect::closeEvent(QCloseEvent *e) {
    cout << "点击关闭按钮" << endl;
    scene->clear();
}

inline void face_detect::showImage(cv::Mat &frame) {
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

void face_detect::init_database() {
    std::cout << "更新" << std::endl;
    auto p = get_abs_path("../datas/face_features");

}

void face_detect::choose_cam_radio_btn_enable(bool f) {
    ui->local_radioButton->setEnabled(f);
    ui->astra_radioButton->setEnabled(f);
}

void graphics_view::set_cam(BaseCamera *_cam) {
    this->cam = _cam;
}

void graphics_view::time_out_slot() {
    if (!cam->checkOpen()) {
        throw runtime_error("link error");
//        std::cout << "send link error1" << std::endl;
//        emit this->link_error();
//        std::cout << "send link error2" << std::endl;
//        return;
    }
    this->cam->updateFrame();
    auto mat = this->cam->getColorMat();
    emit
    this->get_frame(mat);
}

graphics_view::graphics_view(QObject *parent) : QObject(parent) {

}

graphics_view::~graphics_view() {

}
