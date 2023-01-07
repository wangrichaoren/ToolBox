//
// Created by wrc on 22-12-15.
//

#ifndef TOOLBOX_NEWIMAGEWIDGET_H
#define TOOLBOX_NEWIMAGEWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
//using namespace cv;

class newImageWidget : QGraphicsView {
public:

    newImageWidget(QGraphicsView *instance);

    ~newImageWidget() override;

    void showImageFromMat(cv::Mat &mat);

private:
    QGraphicsView *instance{nullptr};
    QGraphicsScene *mScene{nullptr};
};


#endif //TOOLBOX_NEWIMAGEWIDGET_H
