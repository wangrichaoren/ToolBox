//
// Created by wrc on 23-1-10.
//


#include <opencv2/opencv.hpp>
#include "src/AstraCamera.hpp"
#include <iostream>


using namespace std;

int main() {
    int c = 0;
    bool is_reg = false;
    string save_path = "/home/wrc/Desktop/capture_datas";
    AstraCamera cam;
    cam.start(SteamMode::ALL);

    cv::Mat cameraMatrix = cv::Mat_<double>(3, 3);
    cv::Mat discoff = cv::Mat_<double>(1, 5);
    cv::FileStorage paramFs("../config/calib.yaml", cv::FileStorage::READ);
    paramFs["K"] >> cameraMatrix;
    paramFs["D"] >> discoff;

    while (true) {
        cam.updateFrame();
        auto i = cam.getColorMat();
        auto d = cam.getDepthMat();


        cv::Mat i_d;
        // 去畸变
        cv::undistort(i, i_d, cameraMatrix, discoff);

//        imshow("origin color", i);
        imshow("color", i_d);
//        cv::cvtColor(d, d, cv::);

        // 向下10像素
        cv::Mat t_mat = cv::Mat::zeros(2, 3, CV_32FC1);
        t_mat.at<float>(0, 0) = 1;
        t_mat.at<float>(0, 2) = 20; //水平平移量
        t_mat.at<float>(1, 1) = 1;
        t_mat.at<float>(1, 2) = -8; //竖直平移量
        cv::warpAffine(d, d, t_mat, d.size());

        d.convertTo(d, CV_8UC3);
        imshow("depth", d);

        int k = cv::waitKey(30);
//        std::cout<<k<<std::endl;
        if (k == 27) {
            break;
        } else if (k == 32) {
            // 空格拍照
            imwrite(save_path + "/" + to_string(c) + "_color" + ".png", i_d);
            imwrite(save_path + "/" + to_string(c) + "_depth" + ".png", d);
            c += 1;
//            imwrite("./depth.tiff", d);
        } else if (k == 114) {
            // r键盘匹配
            is_reg = !is_reg;
            cam.registration(is_reg);
        }

    }

};