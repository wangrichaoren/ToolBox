//
// Created by wrc on 22-12-16.
//

#include "camera.h"

camera::camera() {
    is_open = false;
    cam_type = local_cam;
}


void camera::closeCam() {
    if (capture.isOpened()) {
        capture.release();
        is_open = false;
        lock1.unlock();
        lock2.unlock();
    }
}

cv::Mat camera::getFrame() {
    lock1.unlock();
    lock2.lock();
    return frame;
}


bool camera::openCam(int idx) {
    capture = cv::VideoCapture(idx);
    if (capture.isOpened()) {
        is_open = true;
        return true;
    }
    return false;
}

void camera::setCameraType(ENUM_CAM type) {
    is_open = false;
    closeCam();
    cam_type = type;
}

void camera::read() {
    while (true) {
        if (!is_open) {
            return;
        }
        lock1.lock();
        capture >> frame;
        lock2.unlock();
    }


}

bool camera::isOpen() {
    if (capture.isOpened()) {
        return true;
    }
    return false;
}
