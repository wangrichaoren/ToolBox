//
// Created by wrc on 23-1-7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_pcl_visual.h" resolved

#include "pcl_visual.h"
#include "ui_pcl_visual.h"


pcl_visual::pcl_visual(QWidget *parent) :
        QDialog(parent), ui(new Ui::pcl_visual) {
    ui->setupUi(this);
    initialVtkWidget();
    // 按钮的信号
    connect(ui->pushButton, &QPushButton::clicked, this, &pcl_visual::onOpen);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &pcl_visual::onFormatConversion);
    qDebug("控件初始化完成.");
}

pcl_visual::~pcl_visual() {
    delete ui;
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

}

void pcl_visual::onOpen() {
    qDebug("点击了打开.");
    std::string fileName = QFileDialog::getOpenFileName(this, "Open PointCloud", ".",
                                                        "Open PCD/PLY files(*.pcd *.ply)").toStdString();
    if (fileName.empty()) {
        std::cout << "未选择点云文件." << std::endl;
        return;
    }
    std::string suffixStr = fileName.substr(fileName.find_last_of('.') + 1);//获取文件后缀

    if (suffixStr == "pcd") {
        pcd_reader.read(fileName, *cloud);
    } else if (suffixStr == "ply") {
        ply_reader.read(fileName, *cloud);
    }

    // todo updatePointCloud这个api真tm傻逼，建议用removePointCloud+addPointCloud来渲染点云
    viewer->removePointCloud("cloud");
//    viewer->resetCameraViewpoint("cloud");
    viewer->addPointCloud(cloud, "cloud");
    viewer->resetCamera();
    ui->qvtkWidget->update();
    qDebug("显示完成.");
}
