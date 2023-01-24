//
// Created by wrc on 23-1-23.
//

#ifndef TOOLBOX_LOCAL_CAMERA_H
#define TOOLBOX_LOCAL_CAMERA_H


#include "base_camera.h"
#include <mutex>

class local_camera : public BaseCamera {
public:
    local_camera();

    ~local_camera();

    inline void close() override;

    void pause(bool f) override;

    bool checkOpen() override;

    inline void updateFrame() override;

    cv::Mat getColorMat() override;

private:
    cv::VideoCapture capture;
    bool is_pause = false;
    cv::Mat mat;
    std::mutex l1;
    std::mutex l2;
};


#endif //TOOLBOX_LOCAL_CAMERA_H
