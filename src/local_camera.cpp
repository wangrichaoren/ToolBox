//
// Created by wrc on 23-1-23.
//

#include "local_camera.h"

local_camera::local_camera() {
    // linux udev固定设备号/多路USB固定设备号。这里的idx为2，实际上是通过rules文件改写的，否则的话每次索引都会不相同，详细 https://blog.csdn.net/limuyuanrs/article/details/108088644
    // todo cv::CAP_V4L2 --- 感觉有点问题
    // 调用opencv的api创建笔记本摄像头的句柄
    capture = cv::VideoCapture(-1, cv::CAP_V4L2);
}

bool local_camera::checkOpen() {
    if (capture.isOpened()) {
        return true;
    }
    return false;
}

void local_camera::updateFrame() {
    if (!is_start){
        throw std::runtime_error("cam must be first start!");
    }
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

void local_camera::start(SteamMode m) {
    if (m != SteamMode::RGB) {
        throw std::runtime_error("local cam only support rgb model!");
    }
    is_start = true;
}
