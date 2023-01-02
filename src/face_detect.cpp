//
// Created by wrc on 22-12-14.
//

// You may need to build the project (run Qt uic code generator) to get "ui_face_detect.h" resolved

#include "face_detect.h"
#include "ui_face_detect.h"


face_detect::face_detect(QWidget *parent) :
        QDialog(parent), ui(new Ui::face_detect) {

    ui->setupUi(this);

    ui->radioButton->setChecked(true);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    is_open_cam = false;
    is_open_det = false;

    scene = new QGraphicsScene;
    cam = new camera();
    face = new ArcFace();

    // 绑定打开相机按钮
    connect(ui->pushButtonOpenCam, &QPushButton::clicked, [=] {
        qDebug("打开相机");
        if (cam->isOpen()){
            showMessageBox(this,"相机已开启");
            return ;
        }
        ENUM_CAM cam_type;
        if (ui->radioButton->isChecked()) {
            cam_type = local_cam;
        } else if (ui->radioButton_2->isChecked()) {
            cam_type = usb_cam;
        }

        if (cam_type == usb_cam) {
            for (int i = 1; i < 10; ++i) {
                bool f = cam->openCam(i);
                if (f) {
                    qDebug("索引%d的USB相机打开成功!", i);
                    break;
                }
                if (i == 9) {
                    showMessageBox(this, "外部USB相机打开异常!请确认是否正确接线!");
                    return;
                }
            }
        } else if (cam_type == local_cam) {
            bool f = cam->openCam(cam_type);
            if (!f) {
                showMessageBox(this, "本地相机打开异常!请确认当前电脑是否正确安装摄像头驱动!");
                return;
            }
        }

        is_open_cam = true;

        ui->radioButton->setEnabled(false);
        ui->radioButton_2->setEnabled(false);

        auto future = QtConcurrent::run([=] {
            cam->read();
        });
        while (!future.isFinished()) {
            if (!is_open_cam) {
                qDebug("检测到停止信号!");
                break;
            }
            scene->clear();

            auto frame = cam->getFrame();

            if (frame.empty()) {
                continue;
            }

            cvtColor(frame, frame, COLOR_BGR2RGB);

            flip(frame, frame, 1);

            // 人脸识别
            if (is_open_det) {
//                qDebug("人脸识别中...");
                frame = face->detect(frame);
            }

            showImage(frame);

            QApplication::processEvents(QEventLoop::AllEvents, 100);
        }

        future.waitForFinished();
        cout << "退出" << endl;
    });

    // 绑定关闭相机按钮
    connect(ui->pushButtonCloseCam, &QPushButton::clicked, [=] {
        qDebug("关闭相机");
        is_open_cam = false;
        is_open_det = false;
        cam->closeCam();
        scene->clear();
        ui->radioButton->setEnabled(true);
        ui->radioButton_2->setEnabled(true);
    });

    // 绑定人脸识别算法
    connect(ui->pushButtonDet, &QPushButton::clicked, [=] {
        if (is_open_det) {
            qDebug("关闭人脸识别");
            is_open_det = false;
            ui->pushButtonDet->setText("开启人脸识别");
        } else {
            qDebug("开启人脸识别");
            is_open_det = true;
            ui->pushButtonDet->setText("关闭人脸识别");
        }
    });


}

face_detect::~face_detect() {
    cout << "xxx face detect" << endl;
    scene->deleteLater();
    delete cam;
    delete face;
    delete ui;
}

void face_detect::closeEvent(QCloseEvent *e) {
    cout << "点击关闭按钮" << endl;
    is_open_cam = false;
    is_open_det = false;
    cam->closeCam();
    scene->clear();
}

inline void face_detect::showImage(Mat &frame) {
//    cout << frame.rows << endl;
//    cout << frame.cols << endl;

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
}

