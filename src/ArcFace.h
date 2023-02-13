//
// Created by wrc on 22-12-17.
//

#ifndef TOOLBOX_ARCFACE_H
#define TOOLBOX_ARCFACE_H

#include "arcsoft_face/arcsoft_face_sdk.h"
#include "arcsoft_face/amcomdef.h"
#include "arcsoft_face/asvloffscreen.h"
#include "arcsoft_face/merror.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <QString>

using namespace std;
//using namespace cv;

#define APPID "AKgVRqi8NpqviMFYs1cVU4HwCxXx7sU8H7nxnuUJuE8Y"
#define SDKKEY "HHXoXkW51gMV7bawRvitxg1akqo5EXXn7T9HZSpM5dHG"

#define SafeFree(p) { if ((p)) free(p); (p) = NULL; }
#define SafeArrayDelete(p) { if ((p)) delete [] (p); (p) = NULL; }
#define SafeDelete(p) { if ((p)) delete (p); (p) = NULL; }

enum DetectMode {
    IMAGE,
    VIDEO
};

struct DetectFaceResult {
    bool flag;
    cv::Mat detect_image;
};

class ArcFace {
public:
    ArcFace();

    ~ArcFace();

    // 人脸识别(离线/在线)
    DetectFaceResult
    detect(cv::Mat &frame, bool is_compare = false, DetectMode= VIDEO,
           vector<std::pair<string, ASF_FaceFeature>> features = {});

    // 人脸特征提取
    std::tuple<bool, ASF_FaceFeature, string, cv::Mat> face_features_extract(const cv::Mat &);


private:
    static void timestampToTime(char *timeStamp, char *dateTime, int dateTimeSize);

    static int
    ColorSpaceConversion(MInt32 width, MInt32 height, MInt32 format, MUInt8 *imgData, ASVLOFFSCREEN &offscreen);

private:
    MHandle video_handle;
    MHandle image_handle;

    MInt32 video_mask;
    MInt32 image_mask;
    MInt32 video_process_mask;
    MInt32 image_process_mask;
//    IplImage img;

};


#endif //TOOLBOX_ARCFACE_H
