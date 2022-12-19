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
#include "camera.h"
#include "utils.h"
#include <QGraphicsScene>
#include <QButtonGroup>
#include "ArcFace.h"


QT_BEGIN_NAMESPACE
namespace Ui { class face_detect; }
QT_END_NAMESPACE

class face_detect : public QDialog {
Q_OBJECT

public:
    explicit face_detect(QWidget *parent = nullptr);

    void closeEvent(QCloseEvent *e);

    ~face_detect() override;


private:
    inline void showImage(Mat &frame);
    Ui::face_detect *ui;
    bool is_open_cam;
    bool is_open_det;
    QGraphicsScene *scene;
    camera *cam;
    ArcFace *face;
};


#endif //TOOLBOX_FACE_DETECT_H
