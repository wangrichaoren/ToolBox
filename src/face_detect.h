//
// Created by wrc on 22-12-14.
//

#ifndef TOOLBOX_FACE_DETECT_H
#define TOOLBOX_FACE_DETECT_H

#include <QDialog>
#include "arcsoft_face/amcomdef.h"
#include "arcsoft_face/arcsoft_face_sdk.h"
#include "arcsoft_face/asvloffscreen.h"
#include "arcsoft_face/merror.h"
#include "imagewidget.h"
#include <QtConcurrent/QtConcurrent>
#include "base_camera.h"
#include "utils.h"
#include <QGraphicsScene>
#include <QButtonGroup>
#include "ArcFace.h"
#include "local_camera.h"
#include "AstraCamera.hpp"
#include "QFileDialog"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <stdio.h>


QT_BEGIN_NAMESPACE
namespace Ui { class face_detect; }
QT_END_NAMESPACE

class graphics_view : public QObject {
Q_OBJECT
private:
    BaseCamera *cam = nullptr;
public:
    explicit graphics_view(QObject *parent = nullptr);

    ~graphics_view();

    void set_cam(BaseCamera *cam);

public slots:

    void time_out_slot();

signals:

    void get_frame(cv::Mat frame);

    void link_error();
};

class face_detect : public QDialog {
Q_OBJECT

public:
    explicit face_detect(QWidget *parent = nullptr);

    void closeEvent(QCloseEvent *e);

    void init_database();

    void show_database();

    ~face_detect() override;

    void choose_cam_radio_btn_enable(bool f);


private:
    inline void showImage(cv::Mat &frame);

    Ui::face_detect *ui;
    QGraphicsScene *scene;
    ArcFace *face;
    QTimer *m_timer;
    BaseCamera *cam;
    QThread *m_thread;
    graphics_view *m_view;
    QSqlDatabase database;
    vector<std::pair<string, ASF_FaceFeature>> m_features;
    vector<std::pair<string, ASF_FaceFeature>> local_feature;


    bool is_online = false;
    bool is_login = false;

signals:

    void online_signal(bool f);
};


#endif //TOOLBOX_FACE_DETECT_H
