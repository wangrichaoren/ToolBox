//
// Created by wrc on 22-12-17.
//

#include "ArcFace.h"

void ArcFace::timestampToTime(char *timeStamp, char *dateTime, int dateTimeSize) {
    time_t tTimeStamp = atoll(timeStamp);
    struct tm *pTm = gmtime(&tTimeStamp);
    strftime(dateTime, dateTimeSize, "%Y-%m-%d %H:%M:%S", pTm);
}

int
ArcFace::ColorSpaceConversion(MInt32 width, MInt32 height, MInt32 format, MUInt8 *imgData, ASVLOFFSCREEN &offscreen) {
    offscreen.u32PixelArrayFormat = (unsigned int) format;
    offscreen.i32Width = width;
    offscreen.i32Height = height;

    switch (offscreen.u32PixelArrayFormat) {
        case ASVL_PAF_RGB24_B8G8R8:
            offscreen.pi32Pitch[0] = offscreen.i32Width * 3;
            offscreen.ppu8Plane[0] = imgData;
            break;
        case ASVL_PAF_I420:
            offscreen.pi32Pitch[0] = width;
            offscreen.pi32Pitch[1] = width >> 1;
            offscreen.pi32Pitch[2] = width >> 1;
            offscreen.ppu8Plane[0] = imgData;
            offscreen.ppu8Plane[1] = offscreen.ppu8Plane[0] + offscreen.i32Height * offscreen.i32Width;
            offscreen.ppu8Plane[2] = offscreen.ppu8Plane[0] + offscreen.i32Height * offscreen.i32Width * 5 / 4;
            break;
        case ASVL_PAF_NV12:
        case ASVL_PAF_NV21:
            offscreen.pi32Pitch[0] = offscreen.i32Width;
            offscreen.pi32Pitch[1] = offscreen.pi32Pitch[0];
            offscreen.ppu8Plane[0] = imgData;
            offscreen.ppu8Plane[1] = offscreen.ppu8Plane[0] + offscreen.pi32Pitch[0] * offscreen.i32Height;
            break;
        case ASVL_PAF_YUYV:
        case ASVL_PAF_DEPTH_U16:
            offscreen.pi32Pitch[0] = offscreen.i32Width * 2;
            offscreen.ppu8Plane[0] = imgData;
            break;
        case ASVL_PAF_GRAY:
            offscreen.pi32Pitch[0] = offscreen.i32Width;
            offscreen.ppu8Plane[0] = imgData;
            break;
        default:
            return 0;
    }
    return 1;
}

ArcFace::ArcFace() {
    printf("\n************* 虹软SDK信息 *****************\n");
    MRESULT res = MOK;
    ASF_ActiveFileInfo activeFileInfo = {0};
    res = ASFGetActiveFileInfo(&activeFileInfo);
    if (res != MOK) {
        printf("ASF 获取活动文件信息 错误: %d\n", res);
    } else {
        //这里仅获取了有效期时间，还需要其他信息直接打印即可
        char startDateTime[32];
        timestampToTime(activeFileInfo.startTime, startDateTime, 32);
        printf("开始时间: %s\n", startDateTime);
        char endDateTime[32];
        timestampToTime(activeFileInfo.endTime, endDateTime, 32);
        printf("结束时间: %s\n", endDateTime);
    }

    //SDK版本信息
    const ASF_VERSION version = ASFGetVersion();
    printf("\nSDK版本号:%s\n", version.Version);
    printf("构建日期:%s\n", version.BuildDate);
    printf("版权:%s\n", version.CopyRight);

    printf("\n************* 在线激活 *****************\n");

    res = ASFOnlineActivation(APPID, SDKKEY);
    if (MOK != res && MERR_ASF_ALREADY_ACTIVATED != res)
        printf("ASF激活错误: %d\n", res);
    else
        printf("ASF激活成功: %d\n", res);

    //初始化引擎
    handle = NULL;
//    MInt32 mask = ASF_FACE_DETECT | ASF_FACERECOGNITION | ASF_AGE | ASF_GENDER | ASF_FACE3DANGLE | ASF_LIVENESS |
//                  ASF_IR_LIVENESS;
//    MInt32 mask = ASF_FACE_DETECT | ASF_FACERECOGNITION | ASF_AGE | ASF_GENDER | ASF_FACE3DANGLE;
    // 目标检测/识别/性别/年龄
    MInt32 mask = ASF_FACE_DETECT | ASF_FACERECOGNITION | ASF_GENDER | ASF_AGE;
    res = ASFInitEngine(ASF_DETECT_MODE_VIDEO, ASF_OP_0_ONLY, NSCALE, FACENUM, mask, &handle);
    if (res != MOK)
        printf("ASF检测引擎初始化失败: %d\n", res);
    else
        printf("ASF检测引擎初始化成功: %d\n", res);
}

ArcFace::~ArcFace() {
    cout << "xxx arcface sdk" << endl;

}

cv::Mat ArcFace::detect(cv::Mat &frame, bool online) {
    auto originalImg = cvIplImage(frame);
    IplImage *img = cvCreateImage(cvSize(originalImg.width - originalImg.width %
                                                             4, originalImg.height), IPL_DEPTH_8U,
                                  originalImg.nChannels);
    CvSize size = cvSize(img->width, img->height);//区域大小
    cvSetImageROI(&originalImg, cvRect(0, 0, size.width, size.height));//设置源图像ROI
    cvCopy(&originalImg, img); //复制图像
    cvResetImageROI(&originalImg);//源图像用完后,清空ROI

    // 构造出的输入图像数据
    ASVLOFFSCREEN offscreen = {0};
    offscreen.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
    offscreen.i32Width = img->width;
    offscreen.i32Height = img->height;
    offscreen.pi32Pitch[0] = img->widthStep;
    offscreen.ppu8Plane[0] = (MUInt8 *) img->imageData;

    ASF_MultiFaceInfo detectedFaces = {0};

    // 其他检测信息-年龄/性别/rpy
    MInt32 processMask = ASF_GENDER | ASF_AGE;

    if (img) {
        MRESULT res = ASFDetectFacesEx(handle, &offscreen, &detectedFaces);
        if (MOK != res) {
            printf("ASF人脸识别错误: %d\n", res);
        } else {
            // 打印人脸检测结果
            res = ASFProcessEx(handle, &offscreen, &detectedFaces, processMask);
            if (res != MOK)
                printf("ASFProcessEx fail: %d\n", res);
            else
                printf("ASFProcessEx sucess: %d\n", res);
            for (int i = 0; i < detectedFaces.faceNum; i++) {
                // 人脸信息
                // 年龄

                ASF_AgeInfo ageInfo = {0};
                res = ASFGetAge(handle, &ageInfo);
                int age = 0;
                if (res == MOK) {
                    printf("年龄:%d\n", ageInfo.ageArray[i]);
                    age = ageInfo.ageArray[i];
                }
                // 性别
                ASF_GenderInfo genderInfo = {0};
                res = ASFGetGender(handle, &genderInfo);
                cv::Scalar c;
                if (res == MOK) {
                    if (genderInfo.genderArray[i] == 0) {
                        c = cv::Scalar(255, 0, 0);
                    } else if (genderInfo.genderArray[i] == 1) {
                        c = cv::Scalar(0, 0, 255);
                    } else {
                        c = cv::Scalar(150, 150, 150);
                    }
                } else {
                    c = cv::Scalar(150, 150, 150);
                }

                //3d角度
//                ASF_Face3DAngle angleInfo = {0};
//                res = ASFGetFace3DAngle(handle, &angleInfo);
//                if (res == MOK) {
//                    printf("3d角度: roll: %lf yaw: %lf pitch: %lf\n", angleInfo.roll[i], angleInfo.yaw[i],
//                           angleInfo.pitch[i]);
//
//                }
//                printf("Face Id: %d\n", detectedFaces.faceID[i]);
//                printf("Face Orient: %d\n", detectedFaces.faceOrient[i]);
                // 绘制到frame:Mat上
                rectangle(frame, cv::Point(detectedFaces.faceRect[i].left, detectedFaces.faceRect[i].top),
                          cv::Point(detectedFaces.faceRect[i].right, detectedFaces.faceRect[i].bottom),
                          c, 2);

                int theta=10;
                if (!online) {
                    rectangle(frame, cv::Point(detectedFaces.faceRect[i].left + theta, detectedFaces.faceRect[i].top + theta),
                              cv::Point(detectedFaces.faceRect[i].right - theta, detectedFaces.faceRect[i].bottom - theta),
                              cv::Scalar(150, 150, 150), 1);
                } else {
                    rectangle(frame, cv::Point(detectedFaces.faceRect[i].left + theta, detectedFaces.faceRect[i].top + theta),
                              cv::Point(detectedFaces.faceRect[i].right - theta, detectedFaces.faceRect[i].bottom - theta),
                              cv::Scalar(0, 255, 0), 1);
                }

                auto dis = (detectedFaces.faceRect[i].right - detectedFaces.faceRect[i].left) / 10;
                for (int j = 1; j < int(age / 10) + 1; ++j) {
                    cv::line(frame, cv::Point(dis * j + detectedFaces.faceRect[i].left, detectedFaces.faceRect[i].top),
                             cv::Point(dis * j + detectedFaces.faceRect[i].left, detectedFaces.faceRect[i].top - 5 * j),
                             c,
                             2);
                }

            }
        }
        //释放图像内存,这里只是做人脸检测,若还需要做特征提取等处理,图像数据没必要释放这么早
        cvReleaseImage(&img);
    }

    return frame;
}

void ArcFace::register_features() {

}


