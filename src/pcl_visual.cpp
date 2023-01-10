//
// Created by wrc on 23-1-7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_pcl_visual.h" resolved

#include "pcl_visual.h"
#include "ui_pcl_visual.h"


pcl_visual::pcl_visual(QWidget *parent) :
        QDialog(parent), ui(new Ui::pcl_visual) {
    ui->setupUi(this);

    ui->pushButton_2->setEnabled(false);
    ui->savePushButton->setEnabled(false);

    initialVtkWidget();

    // 用于显示的绕x旋转
    Eigen::Affine3f rota_x = Eigen::Affine3f::Identity();
    float theta = M_PI;
    rota_x.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitX()));

    // 加载相机内参
    cv::FileStorage paramFs("../config/calib_bak1.yaml", cv::FileStorage::READ);
    camera_fx = paramFs["fx"];
    camera_fy = paramFs["fy"];
    camera_cx = paramFs["cx"];
    camera_cy = paramFs["cy"];

    m_timer = new QTimer;
    m_thread = new QThread;
    m_cam = new CamVisual;
    m_cam->moveToThread(m_thread);

    // 坐标轴
    connect(ui->showCoordPushButton, &QPushButton::clicked, [=] {
        isShowCoord = !isShowCoord;
        if (isShowCoord) {
            ui->showCoordPushButton->setText("隐藏坐标轴");
            viewer->addCoordinateSystem(0.2);
            qDebug("设置显示坐标轴.");
        } else {
            ui->showCoordPushButton->setText("显示坐标轴");
            viewer->removeAllCoordinateSystems();
            qDebug("设置隐藏坐标轴.");
        }
        ui->qvtkWidget->update();
    });

    // 定时器
    connect(m_timer, &QTimer::timeout, m_cam, &CamVisual::timeOutSlot, Qt::DirectConnection);

    connect(m_cam, &CamVisual::sign_send_mat, [=](cv::Mat color, cv::Mat depth) {
        cloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>());
        for (int v = 0; v < depth.rows; v++)
            for (int u = 0; u < depth.cols; u++) {
                // 获取深度图中(m,n)处的值
                ushort d = depth.ptr<ushort>(v)[u];
                // d 可能没有值，若如此，跳过此点
                if (isnan(d) && abs(d) < 0.0001)
                    continue;
                // d 存在值，则向点云增加一个点
                pcl::PointXYZRGB p;

                // 计算这个点的空间坐标
                p.z = float_t(d) / 10000; //单位是米
                p.x = float_t(u - camera_cx) * p.z / camera_fx;
                p.y = float_t(v - camera_cy) * p.z / camera_fy;

                // 从rgb图像中获取它的颜色
                // rgb是三通道的BGR格式图，所以按下面的顺序获取颜色
                cv::Vec3b bgr = color.at<cv::Vec3b>(v, u);
                p.b = bgr[0];
                p.g = bgr[1];
                p.r = bgr[2];

                // 把p加入到点云中
                cloud->points.push_back(p);
            }
//        cloud->height = 1;
//        cloud->width = cloud->points.size();
//        cloud->is_dense = false;
//        viewer->addCoordinateSystem(0.2);
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr show_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
        pcl::transformPointCloud(*cloud, *show_cloud, rota_x);
        viewer->removePointCloud("cloud");
        viewer->addPointCloud<pcl::PointXYZRGB>(show_cloud, "cloud");
        ui->qvtkWidget->update();
    });

    // save push btn
    connect(ui->savePushButton, &QPushButton::clicked, [=] {
        qDebug("点击了保存点云按钮");
        cloud->height = 1;
        cloud->width = cloud->points.size();
        cloud->is_dense = false;
        std::string fileName;
        while (true) {
            auto f = showInputBox(this, "保存点云", "保存的点云名称: ");
            if (!f.first) {
                showMessageBox(this, "点云保存失败!");
                return;
            }
            fileName = f.second;
            if (fileName.empty()) {
                showMessageBox(this, "点云名称不能为空!");
                continue;
            } else {
                break;
            }
        }
        std::string savePath = "../datas/point_clouds/" + fileName + ".pcd";
        pcl::io::savePCDFile(savePath, *cloud, true);
    });

    // 按钮的信号
    connect(ui->pushButton, &QPushButton::clicked, this, &pcl_visual::onOpen);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &pcl_visual::onFormatConversion);

    // 相机刷新的信号与槽
    connect(ui->openPushButton, &QPushButton::clicked, [=] {
        isOpen = !isOpen;
        if (isOpen) {
            m_cam->pause(false);
            ui->openPushButton->setText("关闭相机");
            ui->savePushButton->setEnabled(true);
            m_timer->start();
            m_thread->start();
            qDebug("相机已打开.");

        } else {
            m_cam->pause(true);
            // 移除掉控件显示的点云
            viewer->removePointCloud("cloud");

            ui->openPushButton->setText("开启相机");
            ui->savePushButton->setEnabled(false);
            m_timer->stop();
            m_thread->quit();
            m_thread->wait();
            qDebug("相机已关闭.");
        }
    });

    qDebug("控件初始化完成.");
}

pcl_visual::~pcl_visual() {
    m_thread->quit();
    m_thread->wait();
    delete m_thread;
    delete m_timer;
    delete m_cam;
    delete ui;
    std::cout << "xxx pcl_visual" << std::endl;
}

void pcl_visual::initialVtkWidget() {
    cloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
    viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
    viewer->addPointCloud(cloud, "cloud");
    ui->qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(ui->qvtkWidget->GetInteractor(), ui->qvtkWidget->GetRenderWindow());
    ui->qvtkWidget->update();
}

void pcl_visual::onFormatConversion() {
    qDebug("点击了格式转换.");
    showMessageBox(this, "格式转换懒得开发了,下次一定.");
}

void pcl_visual::onOpen() {
    qDebug("点击了打开.");
    std::string fileName = QFileDialog::getOpenFileName(this, "Open PointCloud", "../datas/point_clouds",
                                                        "Open PCD/PLY files(*.pcd *.ply)").toStdString();
    if (fileName.empty()) {
        std::cout << "未选择点云文件." << std::endl;
        return;
    }
    std::string suffixStr = fileName.substr(fileName.find_last_of('.') + 1);//获取文件后缀
    cloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>());

    if (suffixStr == "pcd") {
        pcd_reader.read(fileName, *cloud);
    } else if (suffixStr == "ply") {
        ply_reader.read(fileName, *cloud);
    }

    // todo updatePointCloud这个api真tm傻逼，建议用removePointCloud+addPointCloud来渲染点云
    viewer->removePointCloud("cloud");
    viewer->addPointCloud(cloud, "cloud");
    viewer->resetCamera();
    ui->qvtkWidget->update();
    qDebug("显示完成.");
}

CamVisual::CamVisual(QObject *parent) : QObject(parent) {
    cam = new AstraCamera;
    cam->start(ALL);
}

CamVisual::~CamVisual() {
    delete cam;
    std::cout << "xxx CamVisual" << std::endl;
}

void CamVisual::timeOutSlot() {
    cam->updateFrame();
    auto cmat = cam->getColorMat();
    auto dmat = cam->getDepthMat();
    emit this->sign_send_mat(cmat, dmat);
}

void CamVisual::pause(bool f) {
    cam->pause(f);
}
