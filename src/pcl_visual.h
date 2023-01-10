//
// Created by wrc on 23-1-7.
//

#ifndef TOOLBOX_PCL_VISUAL_H
#define TOOLBOX_PCL_VISUAL_H

#include <QDialog>
#include <QWidget>
#include <QFileDialog>
#include <vtkRenderWindow.h>
#include<pcl/io/pcd_io.h>
#include<pcl/io/ply_io.h>
#include<pcl/point_types.h>
#include<pcl/visualization/pcl_visualizer.h>
#include "utils.h"
#include "AstraCamera.hpp"
#include <QTimer>
#include <QThread>


QT_BEGIN_NAMESPACE
namespace Ui { class pcl_visual; }
QT_END_NAMESPACE

class CamVisual : public QObject {
Q_OBJECT

public:
    explicit CamVisual(QObject *parent = nullptr);

    ~CamVisual();

    void pause(bool);

public slots:

    void timeOutSlot();

signals:

    void sign_send_mat(cv::Mat, cv::Mat);

private:
    AstraCamera *cam;
};

class pcl_visual : public QDialog {
Q_OBJECT

public:
    explicit pcl_visual(QWidget *parent = nullptr);

    ~pcl_visual() override;

private:
    Ui::pcl_visual *ui;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    pcl::PLYReader ply_reader;
    pcl::PCDReader pcd_reader;
    QTimer *m_timer;
    QThread *m_thread;
    CamVisual *m_cam;

    // 内参数据
    double camera_fx;
    double camera_fy;
    double camera_cx;
    double camera_cy;

    void initialVtkWidget();

    bool isOpen{false};
    bool isShowCoord{false};

private slots:

    void onOpen();

    void onFormatConversion();

};


#endif //TOOLBOX_PCL_VISUAL_H
