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

using namespace std;
//using namespace cv;

#define APPID "AKgVRqi8NpqviMFYs1cVU4HwCxXx7sU8H7nxnuUJuE8Y"
#define SDKKEY "HHXoXkW51gMV7bawRvitxg1akqo5EXXn7T9HZSpM5dHG"

#define NSCALE 32
#define FACENUM    35

#define SafeFree(p) { if ((p)) free(p); (p) = NULL; }
#define SafeArrayDelete(p) { if ((p)) delete [] (p); (p) = NULL; }
#define SafeDelete(p) { if ((p)) delete (p); (p) = NULL; }

class ArcFace {
public:
    ArcFace();

    ~ArcFace();

    // 人脸识别
    cv::Mat detect(cv::Mat &frame, bool online = false);

    // 人脸注册
    void register_features();

    //


private:
    void timestampToTime(char *timeStamp, char *dateTime, int dateTimeSize);

    int ColorSpaceConversion(MInt32 width, MInt32 height, MInt32 format, MUInt8 *imgData, ASVLOFFSCREEN &offscreen);

private:
    MHandle handle;
//    IplImage img;

};


#endif //TOOLBOX_ARCFACE_H
