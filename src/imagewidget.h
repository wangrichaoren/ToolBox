#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QPixmap>
#include <QPainter>
#include <QRectF>
#include <QMouseEvent>
#include <QPointF>
#include <QDragEnterEvent>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsItem>
#include <iostream>
#include <QMenu>
#include <QPen>
#include <QLabel>
#include <QGraphicsView>
#include <QtConcurrent/QtConcurrent>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "utils.h"

using namespace std;
using namespace cv;

#define EDGE_WIDTH  2 //边框宽度
#define EDGPADDING  5

// 枚举的roi拖拽方向+角点
enum EnumDirection {
    dir_mid,
    dir_top,
    dir_bottom,
    dir_left,
    dir_right,
    dir_none,
    dir_top_left,
    dir_top_right,
    dir_bottom_left,
    dir_bottom_right
};

// class ImageWidget : QGraphicsItem
class ImageWidget : public QGraphicsItem {
//    Q_OBJECT
public:
    ImageWidget(QGraphicsView *instance);

    ~ImageWidget();

    bool hasRoiRect();

    Mat getRoiRectToMat();

    Mat getScenceToMat();

    void setImage(QPixmap *pixmap);

    void init();

    void graphics(QImage &image, string path);

    void graphicsImageFromMat(Mat &mat);

    QRectF boundingRect() const;


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
               QWidget *);

    void wheelEvent(QGraphicsSceneWheelEvent *event);

//    EmDirection2 region(const QPointF &point);
    void moveRect(const QPointF &mousePoint);


    void moveRectLine(QGraphicsSceneMouseEvent *, EnumDirection);

    void scaleRect(QGraphicsSceneMouseEvent *, EnumDirection);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    void ResetItemPos();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    qreal getScaleValue() const;

    void setQGraphicsViewWH(int nwidth, int nheight);

    Mat QImage2Mat(QImage const &src);

private:
    QGraphicsView *instance;
    qreal m_scaleValue;
    qreal m_scaleDafault;
    QPixmap m_pix;
    QPointF m_startPos;
    QRectF roirect;
    QGraphicsScene *graphicsScene{nullptr};
    EnumDirection direction;
    string img_path;
};

#endif // IMAGEWIDGET_H