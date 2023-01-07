//
// Created by wrc on 22-12-16.
//

#ifndef TOOLBOX_CAMERA_H
#define TOOLBOX_CAMERA_H

#include <opencv2/opencv.hpp>

//using namespace cv;

#include <unistd.h>
#include <mutex>


enum ENUM_CAM {
    local_cam = 0,
    usb_cam = 1
};

class camera {
public:
    camera();

    ~camera() = default;

    bool openCam(int idx);

    void closeCam();

    cv::Mat getFrame();

    void setCameraType(ENUM_CAM= local_cam);

    void read();

    bool isOpen();

private:
    bool is_open;
    cv::VideoCapture capture;
    ENUM_CAM cam_type;
    cv::Mat frame;
    std::mutex lock1;
    std::mutex lock2;
};


#endif //TOOLBOX_CAMERA_H
