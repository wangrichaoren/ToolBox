//
// Created by wrc on 22-12-15.
//

#include "newImageWidget.h"

newImageWidget::newImageWidget(QGraphicsView *instance) {
    qDebug("build newImageWidget");
    this->instance = instance;
    mScene = new QGraphicsScene;
    instance->setMouseTracking(true);
    instance->setFocusPolicy(Qt::StrongFocus);
    setAcceptDrops(true);
}

newImageWidget::~newImageWidget() {
    delete mScene;
}

void newImageWidget::showImageFromMat(cv::Mat &mat) {
    cvtColor(mat, mat, cv::COLOR_BGR2RGB);
    flip(mat, mat, 1);
    QImage q_img((const unsigned char *) mat.data, mat.cols, mat.rows, mat.step,
                 QImage::Format_RGB888);

    auto v_w = instance->width();
    auto v_h = instance->height();
    instance->setSceneRect(QRectF(-(v_w / 2), -(v_h / 2), v_w,
                                  v_h));
    q_img = q_img.scaled(instance->width(), instance->height(), Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation);
    mScene->addPixmap(QPixmap::fromImage(q_img));
    instance->setScene(mScene);
    instance->setFocus();
}
