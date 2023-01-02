//
// Created by wrc on 22-12-30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_calib.h" resolved

#include "calib.h"
#include "ui_calib.h"


calib::calib(QWidget *parent) :
        QDialog(parent), ui(new Ui::calib) {
    ui->setupUi(this);

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

    // 相机流相关
//    connect(visual_thread, &VisualThread::signIsStartSteam, visual_thread, &VisualThread::slotIsStartSteam,
//            Qt::DirectConnection);

    connect(visual_thread, &VisualThread::sign_send_mat, [=](cv::Mat frame) {
        scene->clear();
        cvtColor(frame, frame, cv::COLOR_BGR2RGB);
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

    connect(ui->pushButton_1, &QPushButton::clicked, [=] {
        isOpen = !isOpen;
        if (isOpen) {
            ui->pushButton_1->setText("关闭相机");
            m_timer->start();
            m_thread->start();
        } else {
            ui->pushButton_1->setText("打开相机");
            m_timer->stop();
            scene->clear();
            m_thread->quit();
            m_thread->wait();
            cout << "thread is running?>>>" << m_thread->isRunning() << endl;
        }
    });

}

calib::~calib() {
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

