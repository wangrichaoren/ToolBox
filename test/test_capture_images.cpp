//
// Created by wrc on 23-1-10.
//


#include <opencv2/opencv.hpp>
#include "src/AstraCamera.hpp"
#include <iostream>


using namespace std;

int main() {
    int c = 0;
    string save_path = "/home/wrc/Desktop/calib_images";
    AstraCamera cam;
//    cam.start(SteamMode::ALL);
    cam.start(SteamMode::RGB);
    while (true) {
        cam.updateFrame();
        auto i = cam.getColorMat();
//        auto d = cam.getDepthMat();
        imshow("color", i);
//        imshow("depth", d);
        int k = cv::waitKey(30);
        if (k == 27) {
            break;
        } else if (k == 32) {
            // 空格拍照
            imwrite(save_path + "/" + to_string(c) + ".png", i);
            c += 1;
//            imwrite("./depth.tiff", d);
        }

    }

};