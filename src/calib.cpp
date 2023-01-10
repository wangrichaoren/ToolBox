//
// Created by wrc on 22-12-30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_calib.h" resolved

#include "calib.h"
#include "ui_calib.h"


calib::calib(QWidget *parent) :
        QDialog(parent), ui(new Ui::calib) {
    ui->setupUi(this);

    ui->pushButton_2->setEnabled(false);
    ui->pushButton_4->setEnabled(false);

    // 默认选择棋盘格
    ui->radioButton->setChecked(true);
    // todo 圆网格未实现
    ui->radioButton_2->setEnabled(false);

    setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene;

    m_timer = new QTimer();

    // 开一个新线程
    m_thread = new QThread;

    visual_thread = new VisualThread;

    // 将用于获取相机数据的对象转移到线程中
    visual_thread->moveToThread(m_thread);

    //Qt::DirectConnection这个参数很关键， Qt::DirectConnection：信号发出后立即调用槽函数，槽函数在发出信号的线程中执行。
    //                                  Qt::QueuedConnection：当控制权返还给接收者信号的事件循环中时，开始调用槽函数。槽函数在接收者的线程中执行。
    connect(m_timer, SIGNAL(timeout()), visual_thread,
            SLOT(timeOutSlot()), Qt::DirectConnection);

    connect(ui->pushButton_4, &QPushButton::clicked, [=] { isCap = true; });

    connect(ui->pushButton_2, &QPushButton::clicked, [=] {
        cout << "标定计算..." << endl;
        cv::calibrateCamera(objpoints, imgpoints, size1, cameraMatrix, distCoeffs, r, t);

        cv::FileStorage fs("../config/calib_bak1.yaml", cv::FileStorage::WRITE);
        fs << "ImageWidth" << size1.width;
        fs << "ImageHeight" << size1.height;
        fs << "CameraMatrix" << cameraMatrix << "DistCoeffs" << distCoeffs;
        time_t rawtime;
        time(&rawtime);
        fs << "CalibrationDate" << asctime(localtime(&rawtime));
        fs.release();

        showMessageBox(this, "相机标定完成!");

        // 清空进度条
        value = 0;
        ui->progressBar->setValue(0);
        // 清掉数组列表
        objpoints.clear();
        imgpoints.clear();
    });

    connect(ui->progressBar, &QProgressBar::valueChanged, [=](int v) {
        if (v == 100) {
            ui->pushButton_2->setEnabled(true);
        } else if (v == 0) {
            ui->pushButton_2->setEnabled(false);
        }
    });

    connect(visual_thread, &VisualThread::sign_send_mat, [=](cv::Mat frame) {
        if (isFirst) {
            size1.height = frame.rows;
            size1.width = frame.cols;
            isFirst = false;
        }

        scene->clear();
        // color
        cv::Mat originMat;
        cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        frame.copyTo(originMat);
        // gray
        cv::Mat gray;
        cvtColor(frame, gray, cv::COLOR_RGB2GRAY);

        std::vector<cv::Point2f> corner;

        bool f = cv::findChessboardCorners(gray, cv::Size(patternSize.longitudinal, patternSize.transverse), corner,
                                           cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK |
                                           cv::CALIB_CB_NORMALIZE_IMAGE);

        if (f) {
            ui->pushButton_4->setEnabled(true);

            cv::TermCriteria criteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.001);
            cv::cornerSubPix(gray, corner, cv::Size(11, 11), cv::Size(-1, -1), criteria);
            cv::drawChessboardCorners(frame, cv::Size(patternSize.longitudinal, patternSize.transverse), corner, f);

            // 只有检测到角点才能拍照
            if (isCap) {
                cv::bitwise_not(frame, frame);
                std::vector<cv::Point3f> objp;
                // 初始化点，cv::Point3f(j, i, 0) 保存的是 x,y,z 坐标。
                for (int i = 0; i < patternSize.transverse; i++) {
                    for (int j = 0; j < patternSize.longitudinal; j++) {
                        objp.emplace_back(i * patternSize.dis * 0.01, j * patternSize.transverse * 0.01, 0);
                    }
                }
                // todo 这里做角点的push back操作....
                imgpoints.push_back(corner);
                objpoints.push_back(objp);

                isCap = false;
                value += 5;
                ui->progressBar->setValue(value);
                cout << "标定进度: " << value << "%" << endl;
            }
        } else {
            ui->pushButton_4->setEnabled(false);
        }
        // 用于控件显示
        QImage q_img((const unsigned char *) frame.data, frame.cols, frame.rows, frame.step,
                     QImage::Format_RGB888);
        auto iw = q_img.width();
        auto ih = q_img.height();
        auto gw = ui->graphicsView->width();
        auto gh = ui->graphicsView->height();
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
        ui->graphicsView->setScene(scene);
    });

    connect(ui->progressBar, &QProgressBar::valueChanged, [=](int v) {
        if (v == 100) {
            ui->pushButton_2->setEnabled(true);
        }
    });

    connect(ui->pushButton_1, &QPushButton::clicked, [=] {
        isOpen = !isOpen;
        if (isOpen) {
            ui->pushButton_1->setText("关闭相机");
            // 设置patern size
            patternSize.longitudinal = ui->lineEdit->text().toInt();
            patternSize.transverse = ui->lineEdit_2->text().toInt();
            patternSize.dis = ui->lineEdit_3->text().toInt();
            ui->radioButton->setEnabled(false);
            ui->lineEdit->setEnabled(false);
            ui->lineEdit_2->setEnabled(false);
            ui->lineEdit_3->setEnabled(false);
            m_timer->start();
            m_thread->start();
        } else {
            ui->pushButton_1->setText("打开相机");
            ui->radioButton->setEnabled(true);
            ui->lineEdit->setEnabled(true);
            ui->lineEdit_2->setEnabled(true);
            ui->lineEdit_3->setEnabled(true);
            m_timer->stop();
            scene->clear();
            m_thread->quit();
            m_thread->wait();
            ui->pushButton_4->setEnabled(false);
            cout << "thread is running?>>>" << m_thread->isRunning() << endl;
        }
    });

    connect(ui->pushButton_3, &QPushButton::clicked, [=] {
        this->close();
    });


}

calib::~calib() {
    m_thread->quit();
    m_thread->wait();
    delete m_thread;
    delete m_timer;
    delete visual_thread;
    delete scene;
    delete ui;
    cout << "xxx calib ui" << endl;
}


void VisualThread::timeOutSlot() {
    cam->updateFrame();
    auto mat = cam->getColorMat();
    emit this->sign_send_mat(mat);
}

VisualThread::VisualThread(QObject *parent) : QObject(parent) {
    cam = new AstraCamera;
    cam->start(RGB);
}

VisualThread::~VisualThread() {
    delete cam;
    cout << "xxx VisualThread" << endl;
}

