//
// Created by wrc on 22-12-30.
//

#ifndef TOOLBOX_CALIB_H
#define TOOLBOX_CALIB_H

#include <QDialog>
#include <QThread>
#include "AstraCamera.hpp"
#include <iostream>
#include <QGraphicsScene>
#include <QTimer>
#include "utils.h"
#include <QKeyEvent>
#include <opencv2/calib3d.hpp>
#include <yaml-cpp/yaml.h>


using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class calib; }
QT_END_NAMESPACE


class VisualThread : public QObject {
Q_OBJECT

public:
    explicit VisualThread(QObject *parent = nullptr);

    ~VisualThread();

public slots:

    void timeOutSlot();

signals:

    void sign_send_mat(cv::Mat);

private:
    AstraCamera *cam;
};


class calib : public QDialog {
Q_OBJECT

public:
    explicit calib(QWidget *parent = nullptr);

    ~calib() override;


private:
    Ui::calib *ui;
    QTimer *m_timer;
    QThread *m_thread;
    VisualThread *visual_thread;
    QGraphicsScene *scene;
    bool isOpen = false;
    bool isFirst = true;
//    bool isCalib = false;
    bool isCap = false;
    int value = 0;
    cv::Size size1;

    // 输出的相机内参、畸变等信息
    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;
    cv::Mat t;
    cv::Mat r;

    std::vector<std::vector<cv::Point3f> > objpoints;
    std::vector<std::vector<cv::Point2f> > imgpoints;

signals:


};


#endif //TOOLBOX_CALIB_H
