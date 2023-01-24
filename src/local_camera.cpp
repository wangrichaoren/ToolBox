//
// Created by wrc on 23-1-23.
//

#include "local_camera.h"

local_camera::local_camera() {
    capture = cv::VideoCapture(0);
}

bool local_camera::checkOpen() {
    if (capture.isOpened()) {
        return true;
    }
    return false;
}

void local_camera::updateFrame() {
    if (!capture.isOpened()) {
        throw std::runtime_error("local camera link error!");
    }
    l1.lock();
    if (!is_pause) {
        capture >> mat;
    }
    l2.unlock();
}

void local_camera::pause(bool f) {
    is_pause = f;
}

cv::Mat local_camera::getColorMat() {
    l1.unlock();
    l2.lock();
    cv::flip(mat, mat, 1);
    return mat;
}

void local_camera::close() {
    if (!capture.isOpened()) {
        return;
    }
    capture.release();
    is_pause = false;
    l1.unlock();
    l2.unlock();
}

local_camera::~local_camera() {
    if (capture.isOpened()) {
        this->close();
    }
    std::cout << "xxx local camera" << std::endl;
}
