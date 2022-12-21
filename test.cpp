//#include "arcsoft_face/arcsoft_face_sdk.h"
//#include "arcsoft_face/amcomdef.h"
//#include "arcsoft_face/asvloffscreen.h"
//#include "arcsoft_face/merror.h"
//#include <iostream>
//#include <string>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//
//using namespace std;
//
////从开发者中心获取APPID/SDKKEY(以下均为假数据，请替换)
//#define APPID "AKgVRqi8NpqviMFYs1cVU4HwCxXx7sU8H7nxnuUJuE8Y"
//#define SDKKEY "HHXoXkW51gMV7bawRvitxg1akqo5EXXn7T9HZSpM5dHG"
//
//#define NSCALE 16
//#define FACENUM	5
//
//#define SafeFree(p) { if ((p)) free(p); (p) = NULL; }
//#define SafeArrayDelete(p) { if ((p)) delete [] (p); (p) = NULL; }
//#define SafeDelete(p) { if ((p)) delete (p); (p) = NULL; }
//
////时间戳转换为日期格式
//void timestampToTime(char* timeStamp, char* dateTime, int dateTimeSize)
//{
//    time_t tTimeStamp = atoll(timeStamp);
//    struct tm* pTm = gmtime(&tTimeStamp);
//    strftime(dateTime, dateTimeSize, "%Y-%m-%d %H:%M:%S", pTm);
//}
//
////图像颜色格式转换
//int ColorSpaceConversion(MInt32 width, MInt32 height, MInt32 format, MUInt8* imgData, ASVLOFFSCREEN& offscreen)
//{
//    offscreen.u32PixelArrayFormat = (unsigned int)format;
//    offscreen.i32Width = width;
//    offscreen.i32Height = height;
//
//    switch (offscreen.u32PixelArrayFormat)
//    {
//        case ASVL_PAF_RGB24_B8G8R8:
//            offscreen.pi32Pitch[0] = offscreen.i32Width * 3;
//            offscreen.ppu8Plane[0] = imgData;
//            break;
//        case ASVL_PAF_I420:
//            offscreen.pi32Pitch[0] = width;
//            offscreen.pi32Pitch[1] = width >> 1;
//            offscreen.pi32Pitch[2] = width >> 1;
//            offscreen.ppu8Plane[0] = imgData;
//            offscreen.ppu8Plane[1] = offscreen.ppu8Plane[0] + offscreen.i32Height*offscreen.i32Width;
//            offscreen.ppu8Plane[2] = offscreen.ppu8Plane[0] + offscreen.i32Height*offscreen.i32Width * 5 / 4;
//            break;
//        case ASVL_PAF_NV12:
//        case ASVL_PAF_NV21:
//            offscreen.pi32Pitch[0] = offscreen.i32Width;
//            offscreen.pi32Pitch[1] = offscreen.pi32Pitch[0];
//            offscreen.ppu8Plane[0] = imgData;
//            offscreen.ppu8Plane[1] = offscreen.ppu8Plane[0] + offscreen.pi32Pitch[0] * offscreen.i32Height;
//            break;
//        case ASVL_PAF_YUYV:
//        case ASVL_PAF_DEPTH_U16:
//            offscreen.pi32Pitch[0] = offscreen.i32Width * 2;
//            offscreen.ppu8Plane[0] = imgData;
//            break;
//        case ASVL_PAF_GRAY:
//            offscreen.pi32Pitch[0] = offscreen.i32Width;
//            offscreen.ppu8Plane[0] = imgData;
//            break;
//        default:
//            return 0;
//    }
//    return 1;
//}
//
//
//int main()
//{
//    printf("\n************* ArcFace SDK Info *****************\n");
//    MRESULT res = MOK;
//    ASF_ActiveFileInfo activeFileInfo = { 0 };
//    res = ASFGetActiveFileInfo(&activeFileInfo);
//    if (res != MOK)
//    {
//        printf("ASFGetActiveFileInfo fail: %d\n", res);
//    }
//    else
//    {
//        //这里仅获取了有效期时间，还需要其他信息直接打印即可
//        char startDateTime[32];
//        timestampToTime(activeFileInfo.startTime, startDateTime, 32);
//        printf("startTime: %s\n", startDateTime);
//        char endDateTime[32];
//        timestampToTime(activeFileInfo.endTime, endDateTime, 32);
//        printf("endTime: %s\n", endDateTime);
//    }
//
//    //SDK版本信息
//    const ASF_VERSION version = ASFGetVersion();
//    printf("\nVersion:%s\n", version.Version);
//    printf("BuildDate:%s\n", version.BuildDate);
//    printf("CopyRight:%s\n", version.CopyRight);
//
//    printf("\n************* Face Recognition *****************\n");
//
//    res = ASFOnlineActivation(APPID, SDKKEY);
//    if (MOK != res && MERR_ASF_ALREADY_ACTIVATED != res)
//        printf("ASFOnlineActivation fail: %d\n", res);
//    else
//        printf("ASFOnlineActivation sucess: %d\n", res);
//
//    //初始化引擎
//    MHandle handle = NULL;
//    MInt32 mask = ASF_FACE_DETECT | ASF_FACERECOGNITION | ASF_AGE | ASF_GENDER | ASF_FACE3DANGLE | ASF_LIVENESS | ASF_IR_LIVENESS;
//    res = ASFInitEngine(ASF_DETECT_MODE_IMAGE, ASF_OP_0_ONLY, NSCALE, FACENUM, mask, &handle);
//    if (res != MOK)
//        printf("ASFInitEngine fail: %d\n", res);
//    else
//        printf("ASFInitEngine sucess: %d\n", res);
//
//    /*********以下三张图片均存在，图片保存在 ./bulid/images/ 文件夹下*********/
//
//    //可见光图像 NV21格式裸数据
//    char* picPath1 = "/home/wrc/Desktop/ArcSoft_ArcFace_Linux_x64_V3.0/samplecode/ASFTestDemo/images/640x480_1.NV21";
//    int Width1 = 640;
//    int Height1 = 480;
//    int Format1 = ASVL_PAF_NV21;
//    MUInt8* imageData1 = (MUInt8*)malloc(Height1*Width1*3/2);
//    FILE* fp1 = fopen(picPath1, "rb");
//
//    //可见光图像 NV21格式裸数据
//    char* picPath2 = "/home/wrc/Desktop/ArcSoft_ArcFace_Linux_x64_V3.0/samplecode/ASFTestDemo/images/640x480_2.NV21";
//    int Width2 = 640;
//    int Height2 = 480;
//    int Format2 = ASVL_PAF_NV21;
//    MUInt8* imageData2 = (MUInt8*)malloc(Height1*Width1*3/2);
//    FILE* fp2 = fopen(picPath2, "rb");
//
//    //红外图像 NV21格式裸数据
//    char* picPath3 = "/home/wrc/Desktop/ArcSoft_ArcFace_Linux_x64_V3.0/samplecode/ASFTestDemo/images/640x480_3.NV21";
//    int Width3 = 640;
//    int Height3 = 480;
//    int Format3 = ASVL_PAF_GRAY;
//    MUInt8* imageData3 = (MUInt8*)malloc(Height2*Width2);	//只读NV21前2/3的数据为灰度数据
//    FILE* fp3 = fopen(picPath3, "rb");
//
//    if (fp1 && fp2 && fp3)
//    {
//        fread(imageData1, 1, Height1*Width1*3/2, fp1);	//读NV21裸数据
//        fclose(fp1);
//        fread(imageData2, 1, Height1*Width1*3/2, fp2);	//读NV21裸数据
//        fclose(fp2);
//        fread(imageData3, 1, Height3*Width3, fp3);		//读NV21前2/3的数据,用于红外活体检测
//        fclose(fp3);
//
//        ASVLOFFSCREEN offscreen1 = { 0 };
//        ColorSpaceConversion(Width1, Height1, ASVL_PAF_NV21, imageData1, offscreen1);
//
//        //第一张人脸
//        ASF_MultiFaceInfo detectedFaces1 = { 0 };
//        ASF_SingleFaceInfo SingleDetectedFaces = { 0 };
//        ASF_FaceFeature feature1 = { 0 };
//        ASF_FaceFeature copyfeature1 = { 0 };
//
//        res = ASFDetectFacesEx(handle, &offscreen1, &detectedFaces1);;
//        if (res != MOK && detectedFaces1.faceNum > 0)
//        {
//            printf("%s ASFDetectFaces 1 fail: %d\n", picPath1, res);
//        }
//        else
//        {
//            SingleDetectedFaces.faceRect.left = detectedFaces1.faceRect[0].left;
//            SingleDetectedFaces.faceRect.top = detectedFaces1.faceRect[0].top;
//            SingleDetectedFaces.faceRect.right = detectedFaces1.faceRect[0].right;
//            SingleDetectedFaces.faceRect.bottom = detectedFaces1.faceRect[0].bottom;
//            SingleDetectedFaces.faceOrient = detectedFaces1.faceOrient[0];
//
//            // 单人脸特征提取
//            res = ASFFaceFeatureExtractEx(handle, &offscreen1, &SingleDetectedFaces, &feature1);
//            if (res != MOK)
//            {
//                printf("%s ASFFaceFeatureExtractEx 1 fail: %d\n", picPath1, res);
//            }
//            else
//            {
//                //拷贝feature，否则第二次进行特征提取，会覆盖第一次特征提取的数据，导致比对的结果为1
//                copyfeature1.featureSize = feature1.featureSize;
//                copyfeature1.feature = (MByte *)malloc(feature1.featureSize);
//                memset(copyfeature1.feature, 0, feature1.featureSize);
//                memcpy(copyfeature1.feature, feature1.feature, feature1.featureSize);
//            }
//        }
//
//        //第二张人脸
//        ASVLOFFSCREEN offscreen2 = { 0 };
//        ColorSpaceConversion(Width2, Height2, ASVL_PAF_NV21, imageData2, offscreen2);
//
//        ASF_MultiFaceInfo detectedFaces2 = { 0 };
//        ASF_FaceFeature feature2 = { 0 };
//
//        res = ASFDetectFacesEx(handle, &offscreen2, &detectedFaces2);
//        if (res != MOK && detectedFaces2.faceNum > 0)
//        {
//            printf("%s ASFDetectFacesEx 2 fail: %d\n", picPath2, res);
//        }
//        else
//        {
//            SingleDetectedFaces.faceRect.left = detectedFaces2.faceRect[0].left;
//            SingleDetectedFaces.faceRect.top = detectedFaces2.faceRect[0].top;
//            SingleDetectedFaces.faceRect.right = detectedFaces2.faceRect[0].right;
//            SingleDetectedFaces.faceRect.bottom = detectedFaces2.faceRect[0].bottom;
//            SingleDetectedFaces.faceOrient = detectedFaces2.faceOrient[0];
//
//            res = ASFFaceFeatureExtractEx(handle, &offscreen2, &SingleDetectedFaces, &feature2);
//            if (res != MOK)
//                printf("%s ASFFaceFeatureExtractEx 2 fail: %d\n", picPath2, res);
//            else
//                printf("%s ASFFaceFeatureExtractEx 2 sucess: %d\n", picPath2, res);
//        }
//
//        // 单人脸特征比对
//        MFloat confidenceLevel;
//        res = ASFFaceFeatureCompare(handle, &copyfeature1, &feature2, &confidenceLevel);
//        if (res != MOK)
//            printf("ASFFaceFeatureCompare fail: %d\n", res);
//        else
//            printf("ASFFaceFeatureCompare sucess: %lf\n", confidenceLevel);
//
//
//        printf("\n************* Face Process *****************\n");
//        //设置活体置信度 SDK内部默认值为 IR：0.7  RGB：0.5（无特殊需要，可以不设置）
//        ASF_LivenessThreshold threshold = { 0 };
//        threshold.thresholdmodel_BGR = 0.5;
//        threshold.thresholdmodel_IR = 0.7;
//        res = ASFSetLivenessParam(handle, &threshold);
//        if (res != MOK)
//            printf("ASFSetLivenessParam fail: %d\n", res);
//        else
//            printf("RGB Threshold: %f\nIR Threshold: %f\n", threshold.thresholdmodel_BGR, threshold.thresholdmodel_IR);
//
//        // 人脸信息检测
//        MInt32 processMask = ASF_AGE | ASF_GENDER | ASF_FACE3DANGLE | ASF_LIVENESS;
//        res = ASFProcessEx(handle, &offscreen2, &detectedFaces2, processMask);
//        if (res != MOK)
//            printf("ASFProcessEx fail: %d\n", res);
//        else
//            printf("ASFProcessEx sucess: %d\n", res);
//
//        // 获取年龄
//        ASF_AgeInfo ageInfo = { 0 };
//        res = ASFGetAge(handle, &ageInfo);
//        if (res != MOK)
//            printf("%s ASFGetAge fail: %d\n", picPath2, res);
//        else
//            printf("%s First face age: %d\n", picPath2, ageInfo.ageArray[0]);
//
//        // 获取性别
//        ASF_GenderInfo genderInfo = { 0 };
//        res = ASFGetGender(handle, &genderInfo);
//        if (res != MOK)
//            printf("%s ASFGetGender fail: %d\n", picPath2, res);
//        else
//            printf("%s First face gender: %d\n", picPath2, genderInfo.genderArray[0]);
//
//        // 获取3D角度
//        ASF_Face3DAngle angleInfo = { 0 };
//        res = ASFGetFace3DAngle(handle, &angleInfo);
//        if (res != MOK)
//            printf("%s ASFGetFace3DAngle fail: %d\n", picPath2, res);
//        else
//            printf("%s First face 3dAngle: roll: %lf yaw: %lf pitch: %lf\n", picPath2, angleInfo.roll[0], angleInfo.yaw[0], angleInfo.pitch[0]);
//
//        //获取活体信息
//        ASF_LivenessInfo rgbLivenessInfo = { 0 };
//        res = ASFGetLivenessScore(handle, &rgbLivenessInfo);
//        if (res != MOK)
//            printf("ASFGetLivenessScore fail: %d\n", res);
//        else
//            printf("ASFGetLivenessScore sucess: %d\n", rgbLivenessInfo.isLive[0]);
//
//
//        printf("\n**********IR LIVENESS*************\n");
//
//        //第二张人脸
//        ASVLOFFSCREEN offscreen3 = { 0 };
//        ColorSpaceConversion(Width3, Height3, ASVL_PAF_GRAY, imageData3, offscreen3);
//
//        ASF_MultiFaceInfo detectedFaces3 = { 0 };
//        res = ASFDetectFacesEx(handle, &offscreen3, &detectedFaces3);
//        if (res != MOK)
//            printf("ASFDetectFacesEx fail: %d\n", res);
//        else
//            printf("Face num: %d\n", detectedFaces3.faceNum);
//
//        //IR图像活体检测
//        MInt32 processIRMask = ASF_IR_LIVENESS;
//        res = ASFProcessEx_IR(handle, &offscreen3, &detectedFaces3, processIRMask);
//        if (res != MOK)
//            printf("ASFProcessEx_IR fail: %d\n", res);
//        else
//            printf("ASFProcessEx_IR sucess: %d\n", res);
//
//        //获取IR活体信息
//        ASF_LivenessInfo irLivenessInfo = { 0 };
//        res = ASFGetLivenessScore_IR(handle, &irLivenessInfo);
//        if (res != MOK)
//            printf("ASFGetLivenessScore_IR fail: %d\n", res);
//        else
//            printf("IR Liveness: %d\n", irLivenessInfo.isLive[0]);
//
//        //释放内存
//        SafeFree(copyfeature1.feature);
//        SafeArrayDelete(imageData1);
//        SafeArrayDelete(imageData2);
//        SafeArrayDelete(imageData3);
//
//
//        //反初始化
//        res = ASFUninitEngine(handle);
//        if (res != MOK)
//            printf("ASFUninitEngine fail: %d\n", res);
//        else
//            printf("ASFUninitEngine sucess: %d\n", res);
//    }
//    else
//    {
//        printf("No pictures found.\n");
//    }
//
//    getchar();
//    return 0;
//}





// This file is part of the Orbbec Astra SDK [https://orbbec3d.com]
// Copyright (c) 2015-2017 Orbbec 3D
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Be excellent to each other.
#include <SFML/Graphics.hpp>
#include <astra/astra_core/astra_core.hpp>
#include <astra/astra/astra.hpp>
#include "astra/LitDepthVisualizer.hpp"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <astra/key_handler.h>

enum ColorMode
{
    MODE_COLOR,
    MODE_IR_16,
    MODE_IR_RGB,
};

class MultiFrameListener : public astra::FrameListener
{
public:
    using BufferPtr = std::unique_ptr<uint8_t[]>;

    struct StreamView
    {
        sf::Sprite sprite_;
        sf::Texture texture_;
        BufferPtr buffer_;
        int width_{0};
        int height_{0};
    };

    MultiFrameListener()
    {
        prev_ = ClockType::now();
    }

    void init_texture(int width, int height, StreamView& view)
    {
        if (view.buffer_ == nullptr || width != view.width_ || height != view.height_)
        {
            view.width_ = width;
            view.height_ = height;

            // texture is RGBA
            const int byteLength = width * height * 4;

            view.buffer_ = BufferPtr(new uint8_t[byteLength]);

            clear_view(view);

            view.texture_.create(width, height);
            view.sprite_.setTexture(view.texture_, true);
            view.sprite_.setPosition(0, 0);
        }
    }

    void clear_view(StreamView& view)
    {
        const int byteLength = view.width_ * view.height_ * 4;
        std::fill(&view.buffer_[0], &view.buffer_[0] + byteLength, 0);
    }

    void check_fps()
    {
        const float frameWeight = .2f;

        const ClockType::time_point now = ClockType::now();
        const float elapsedMillis = std::chrono::duration_cast<DurationType>(now - prev_).count();

        elapsedMillis_ = elapsedMillis * frameWeight + elapsedMillis_ * (1.f - frameWeight);
        prev_ = now;

        const float fps = 1000.f / elapsedMillis;

        const auto precision = std::cout.precision();

        std::cout << std::fixed
                  << std::setprecision(1)
                  << fps << " fps ("
                  << std::setprecision(1)
                  << elapsedMillis_ << " ms)"
                  << std::setprecision(precision)
                  << std::endl;
    }

    void update_depth(astra::Frame& frame)
    {
        const astra::PointFrame pointFrame = frame.get<astra::PointFrame>();
        if (!pointFrame.is_valid())
        {
            clear_view(depthView_);
            depthView_.texture_.update(&depthView_.buffer_[0]);
            return;
        }

        const int depthWidth = pointFrame.width();
        const int depthHeight = pointFrame.height();

        init_texture(depthWidth, depthHeight, depthView_);

        if (isPaused_) { return; }

        visualizer_.update(pointFrame);

        astra::RgbPixel* vizBuffer = visualizer_.get_output();
        uint8_t* buffer = &depthView_.buffer_[0];
        for (int i = 0; i < depthWidth * depthHeight; i++)
        {
            const int rgbaOffset = i * 4;
            buffer[rgbaOffset] = vizBuffer[i].r;
            buffer[rgbaOffset + 1] = vizBuffer[i].g;
            buffer[rgbaOffset + 2] = vizBuffer[i].b;
            buffer[rgbaOffset + 3] = 255;
        }

        depthView_.texture_.update(&depthView_.buffer_[0]);
    }

    void update_color(astra::Frame& frame)
    {
        const astra::ColorFrame colorFrame = frame.get<astra::ColorFrame>();

        if (!colorFrame.is_valid())
        {
            clear_view(colorView_);
            colorView_.texture_.update(&colorView_.buffer_[0]);
            return;
        }

        const int colorWidth = colorFrame.width();
        const int colorHeight = colorFrame.height();

        init_texture(colorWidth, colorHeight, colorView_);

        if (isPaused_) { return; }

        const astra::RgbPixel* color = colorFrame.data();
        uint8_t* buffer = &colorView_.buffer_[0];

        for(int i = 0; i < colorWidth * colorHeight; i++)
        {
            const int rgbaOffset = i * 4;
            buffer[rgbaOffset] = color[i].r;
            buffer[rgbaOffset + 1] = color[i].g;
            buffer[rgbaOffset + 2] = color[i].b;
            buffer[rgbaOffset + 3] = 255;
        }

        colorView_.texture_.update(&colorView_.buffer_[0]);
    }

    void update_ir_16(astra::Frame& frame)
    {
        const astra::InfraredFrame16 irFrame = frame.get<astra::InfraredFrame16>();

        if (!irFrame.is_valid())
        {
            clear_view(colorView_);
            colorView_.texture_.update(&colorView_.buffer_[0]);
            return;
        }

        const int irWidth = irFrame.width();
        const int irHeight = irFrame.height();

        init_texture(irWidth, irHeight, colorView_);

        if (isPaused_) { return; }

        const uint16_t* ir_values = irFrame.data();
        uint8_t* buffer = &colorView_.buffer_[0];
        for (int i = 0; i < irWidth * irHeight; i++)
        {
            const int rgbaOffset = i * 4;
            const uint16_t value = ir_values[i];
            const uint8_t red = static_cast<uint8_t>(value >> 2);
            const uint8_t blue = 0x66 - red / 2;
            buffer[rgbaOffset] = red;
            buffer[rgbaOffset + 1] = 0;
            buffer[rgbaOffset + 2] = blue;
            buffer[rgbaOffset + 3] = 255;
        }

        colorView_.texture_.update(&colorView_.buffer_[0]);
    }

    void update_ir_rgb(astra::Frame& frame)
    {
        const astra::InfraredFrameRgb irFrame = frame.get<astra::InfraredFrameRgb>();

        if (!irFrame.is_valid())
        {
            clear_view(colorView_);
            colorView_.texture_.update(&colorView_.buffer_[0]);
            return;
        }

        int irWidth = irFrame.width();
        int irHeight = irFrame.height();

        init_texture(irWidth, irHeight, colorView_);

        if (isPaused_) { return; }

        const astra::RgbPixel* irRGB = irFrame.data();
        uint8_t* buffer = &colorView_.buffer_[0];
        for (int i = 0; i < irWidth * irHeight; i++)
        {
            const int rgbaOffset = i * 4;
            buffer[rgbaOffset] = irRGB[i].r;
            buffer[rgbaOffset + 1] = irRGB[i].g;
            buffer[rgbaOffset + 2] = irRGB[i].b;
            buffer[rgbaOffset + 3] = 255;
        }

        colorView_.texture_.update(&colorView_.buffer_[0]);
    }

    virtual void on_frame_ready(astra::StreamReader& reader,
                                astra::Frame& frame) override
    {
        update_depth(frame);

        switch (colorMode_)
        {
            case MODE_COLOR:
                update_color(frame);
                break;
            case MODE_IR_16:
                update_ir_16(frame);
                break;
            case MODE_IR_RGB:
                update_ir_rgb(frame);
                break;
        }

        check_fps();
    }

    void draw_to(sf::RenderWindow& window, sf::Vector2f origin, sf::Vector2f size)
    {
        const int viewSize = (int)(size.x / 2.0f);
        const sf::Vector2f windowSize = window.getView().getSize();

        if (depthView_.buffer_ != nullptr)
        {
            const float depthScale = viewSize / (float)depthView_.width_;
            const int horzCenter = origin.y * windowSize.y;

            depthView_.sprite_.setScale(depthScale, depthScale);
            depthView_.sprite_.setPosition(origin.x * windowSize.x, horzCenter);
            window.draw(depthView_.sprite_);
        }

        if (colorView_.buffer_ != nullptr)
        {
            const float colorScale = viewSize / (float)colorView_.width_;
            const int horzCenter = origin.y * windowSize.y;

            colorView_.sprite_.setScale(colorScale, colorScale);

            if (overlayDepth_)
            {
                colorView_.sprite_.setPosition(origin.x * windowSize.x, horzCenter);
                colorView_.sprite_.setColor(sf::Color(255, 255, 255, 128));
            }
            else
            {
                colorView_.sprite_.setPosition(origin.x * windowSize.x + viewSize, horzCenter);
                colorView_.sprite_.setColor(sf::Color(255, 255, 255, 255));
            }

            window.draw(colorView_.sprite_);
        }
    }

    void toggle_depth_overlay()
    {
        overlayDepth_ = !overlayDepth_;
    }

    bool get_overlay_depth() const
    {
        return overlayDepth_;
    }

    void toggle_paused()
    {
        isPaused_ = !isPaused_;
    }

    bool is_paused() const
    {
        return isPaused_;
    }

    ColorMode get_mode() const { return colorMode_; }
    void set_mode(ColorMode mode) { colorMode_ = mode; }

private:
    samples::common::LitDepthVisualizer visualizer_;

    using DurationType = std::chrono::milliseconds;
    using ClockType = std::chrono::high_resolution_clock;

    ClockType::time_point prev_;
    float elapsedMillis_{.0f};

    StreamView depthView_;
    StreamView colorView_;
    ColorMode colorMode_;
    bool overlayDepth_{ false };
    bool isPaused_{ false };
};

astra::DepthStream configure_depth(astra::StreamReader& reader)
{
    auto depthStream = reader.stream<astra::DepthStream>();

    auto oldMode = depthStream.mode();

    //We don't have to set the mode to start the stream, but if you want to here is how:
    astra::ImageStreamMode depthMode;

    depthMode.set_width(640);
    depthMode.set_height(480);
    depthMode.set_pixel_format(astra_pixel_formats::ASTRA_PIXEL_FORMAT_DEPTH_MM);
    depthMode.set_fps(30);

    depthStream.set_mode(depthMode);

    auto newMode = depthStream.mode();
    printf("Changed depth mode: %dx%d @ %d -> %dx%d @ %d\n",
           oldMode.width(), oldMode.height(), oldMode.fps(),
           newMode.width(), newMode.height(), newMode.fps());

    return depthStream;
}

astra::InfraredStream configure_ir(astra::StreamReader& reader, bool useRGB)
{
    auto irStream = reader.stream<astra::InfraredStream>();

    auto oldMode = irStream.mode();

    astra::ImageStreamMode irMode;
    irMode.set_width(640);
    irMode.set_height(480);

    if (useRGB)
    {
        irMode.set_pixel_format(astra_pixel_formats::ASTRA_PIXEL_FORMAT_RGB888);
    }
    else
    {
        irMode.set_pixel_format(astra_pixel_formats::ASTRA_PIXEL_FORMAT_GRAY16);
    }

    irMode.set_fps(30);
    irStream.set_mode(irMode);

    auto newMode = irStream.mode();
    printf("Changed IR mode: %dx%d @ %d -> %dx%d @ %d\n",
           oldMode.width(), oldMode.height(), oldMode.fps(),
           newMode.width(), newMode.height(), newMode.fps());

    return irStream;
}

astra::ColorStream configure_color(astra::StreamReader& reader)
{
    auto colorStream = reader.stream<astra::ColorStream>();

    auto oldMode = colorStream.mode();

    astra::ImageStreamMode colorMode;
    colorMode.set_width(640);
    colorMode.set_height(480);
    colorMode.set_pixel_format(astra_pixel_formats::ASTRA_PIXEL_FORMAT_RGB888);
    colorMode.set_fps(30);

    colorStream.set_mode(colorMode);

    auto newMode = colorStream.mode();
    printf("Changed color mode: %dx%d @ %d -> %dx%d @ %d\n",
           oldMode.width(), oldMode.height(), oldMode.fps(),
           newMode.width(), newMode.height(), newMode.fps());

    return colorStream;
}

int main(int argc, char** argv)
{
    astra::initialize();

    set_key_handler();

#ifdef _WIN32
    auto fullscreenStyle = sf::Style::None;
#else
    auto fullscreenStyle = sf::Style::Fullscreen;
#endif

    const sf::VideoMode fullScreenMode = sf::VideoMode::getFullscreenModes()[0];
    const sf::VideoMode windowedMode(2000, 675);

    bool isFullScreen = false;
    sf::RenderWindow window(windowedMode, "Stream Viewer");

    astra::StreamSet streamSet;
    astra::StreamReader reader = streamSet.create_reader();

    reader.stream<astra::PointStream>().start();

    auto depthStream = configure_depth(reader);
    depthStream.start();

    auto colorStream = configure_color(reader);
    colorStream.start();

    auto irStream = configure_ir(reader, false);

    MultiFrameListener listener;
    listener.set_mode(MODE_COLOR);

    reader.add_listener(listener);

    while (window.isOpen())
    {
        astra_update();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                {
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        case sf::Keyboard::F:
                            if (isFullScreen)
                            {
                                isFullScreen = false;
                                window.create(windowedMode, "Stream Viewer", sf::Style::Default);
                            }
                            else
                            {
                                isFullScreen = true;
                                window.create(fullScreenMode, "Stream Viewer", fullscreenStyle);
                            }
                            break;
                        case sf::Keyboard::R:
                            depthStream.enable_registration(!depthStream.registration_enabled());
                            break;
                        case sf::Keyboard::M:
                        {
                            const bool newMirroring = !depthStream.mirroring_enabled();
                            depthStream.enable_mirroring(newMirroring);
                            colorStream.enable_mirroring(newMirroring);
                            irStream.enable_mirroring(newMirroring);
                        }
                            break;
                        case sf::Keyboard::G:
                            colorStream.stop();
                            configure_ir(reader, false);
                            listener.set_mode(MODE_IR_16);
                            irStream.start();
                            break;
                        case sf::Keyboard::I:
                            colorStream.stop();
                            configure_ir(reader, true);
                            listener.set_mode(MODE_IR_RGB);
                            irStream.start();
                            break;
                        case sf::Keyboard::O:
                            listener.toggle_depth_overlay();
                            if (listener.get_overlay_depth())
                            {
                                depthStream.enable_registration(true);
                            }
                            break;
                        case sf::Keyboard::P:
                            listener.toggle_paused();
                            break;
                        case sf::Keyboard::C:
                            if (event.key.control)
                            {
                                window.close();
                            }
                            else
                            {
                                irStream.stop();
                                listener.set_mode(MODE_COLOR);
                                colorStream.start();
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
        listener.draw_to(window, sf::Vector2f(0.f, 0.f), sf::Vector2f(window.getSize().x, window.getSize().y));
        window.display();

        if (!shouldContinue)
        {
            window.close();
        }
    }

    astra::terminate();
    return 0;
}
