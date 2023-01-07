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
    connect(ui->pushButton, &QPushButton::clicked, this, &pcl_visual::onOpen);
}

pcl_visual::~pcl_visual() {
    delete ui;
}

void pcl_visual::initialVtkWidget() {
    cloud.reset(new pcl::PointCloud<pcl::PointXYZ>);
    viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
    viewer->addPointCloud(cloud, "cloud");
    ui->qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(ui->qvtkWidget->GetInteractor(), ui->qvtkWidget->GetRenderWindow());
    ui->qvtkWidget->update();
}

void pcl_visual::onOpen() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open PointCloud", ".", "Open PCD files(*.pcd)");
    pcl::io::loadPCDFile(fileName.toStdString(), *cloud);
    viewer->updatePointCloud(cloud, "cloud");
    viewer->resetCamera();
    ui->qvtkWidget->update();
}
