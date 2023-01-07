//
// Created by wrc on 23-1-7.
//

#ifndef TOOLBOX_PCL_VISUAL_H
#define TOOLBOX_PCL_VISUAL_H

#include <QDialog>
//#pragma once
#include <QWidget>
#include <QFileDialog>
#include <vtkRenderWindow.h>
#include<pcl/io/pcd_io.h>
#include<pcl/io/ply_io.h>
#include<pcl/point_types.h>
#include<pcl/visualization/pcl_visualizer.h>


QT_BEGIN_NAMESPACE
namespace Ui { class pcl_visual; }
QT_END_NAMESPACE

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

    void initialVtkWidget();

private slots:

    void onOpen();

    void onFormatConversion();

};


#endif //TOOLBOX_PCL_VISUAL_H
