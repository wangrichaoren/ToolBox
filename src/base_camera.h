//
// Created by wrc on 23-1-23.
//

#ifndef TOOLBOX_BASE_CAMERA_H
#define TOOLBOX_BASE_CAMERA_H

/**相机基类，所有相机必须继承此类**/

#include <opencv2/opencv.hpp>

class BaseCamera {

public:
    virtual inline void close() = 0;

    virtual void pause(bool f) = 0;

    virtual bool checkOpen() = 0;

    virtual inline void updateFrame() = 0;

    virtual cv::Mat getColorMat() = 0;


};



#endif //TOOLBOX_BASE_CAMERA_H