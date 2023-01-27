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


};

class face_detect : public QDialog {
Q_OBJECT

public:
    explicit face_detect(QWidget *parent = nullptr);

    void closeEvent(QCloseEvent *e);

    void init_database();

    ~face_detect() override;


private:
    inline void showImage(cv::Mat &frame);

    Ui::face_detect *ui;
    QGraphicsScene *scene;
    ArcFace *face;
    QTimer *m_timer;
    BaseCamera *cam;
    QThread *m_thread;
    graphics_view *m_view;

    bool is_online = false;

};


#endif //TOOLBOX_FACE_DETECT_H
