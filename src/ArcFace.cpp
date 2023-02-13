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
    MRESULT res = MOK;
    ASF_ActiveFileInfo activeFileInfo = {nullptr};
    res = ASFGetActiveFileInfo(&activeFileInfo);
    if (res != MOK) {
        throw runtime_error(&"ASF SDK激活信息错误: "[res]);
    }
    char endDateTime[32];
    timestampToTime(activeFileInfo.endTime, endDateTime, 32);
    std::cout << "ASF SDK使用结束时间: " << endDateTime << std::endl;

    //SDK版本信息
    const ASF_VERSION version = ASFGetVersion();
    printf("\nSDK版本号:%s\n", version.Version);
    printf("构建日期:%s\n", version.BuildDate);
    printf("版权:%s\n", version.CopyRight);

    res = ASFOnlineActivation(APPID, SDKKEY);
    if (MOK != res && MERR_ASF_ALREADY_ACTIVATED != res) {
        throw runtime_error(&"ASF SDK激活错误: "[res]);
    }
    std::cout << "ASF 激活成功: " << res << std::endl;

    //初始化引擎
    video_handle = NULL;
    image_handle = NULL;
    // 视频流选项 人脸检测/人脸特征/性别/年龄/RGB活体
    video_mask = ASF_FACE_DETECT | ASF_FACERECOGNITION | ASF_GENDER | ASF_AGE | ASF_LIVENESS;
    // 图片流选项 人脸检测/人脸特征/性别/年龄
    image_mask = ASF_FACE_DETECT | ASF_FACERECOGNITION | ASF_GENDER | ASF_AGE;
    // 附加选项(必须建立在视频流，图片流引擎的选项上。即交集。)
    video_process_mask = ASF_GENDER | ASF_AGE | ASF_LIVENESS;
    image_process_mask = ASF_GENDER | ASF_AGE;
    // 官方建议视频的scale val=16,图片的scale val=32
    res = ASFInitEngine(ASF_DETECT_MODE_VIDEO, ASF_OP_0_ONLY, 16, 50, video_mask, &video_handle);
    if (res != MOK) {
        throw runtime_error(&"ASF 视频流句柄初始化失败: "[res]);
    }
    std::cout << "ASF 视频流句柄初始化成功" << std::endl;

    res = ASFInitEngine(ASF_DETECT_MODE_IMAGE, ASF_OP_0_ONLY, 32, 1, image_mask, &image_handle);
    if (res != MOK) {
        throw runtime_error(&"ASF 图片流句柄初始化失败: "[res]);
    }
    std::cout << "ASF 图片流句柄初始化成功" << std::endl;
}

ArcFace::~ArcFace() {
    cout << "xxx arcface sdk" << endl;
}

/**
 * 核心接口
 * @param frame cv::Mat格式的数据输入
 * @param is_compare 是否进行特征比对
 * @return
 */
DetectFaceResult ArcFace::detect(cv::Mat &frame, bool is_compare, DetectMode detect_mode,
                                 vector<std::pair<string, ASF_FaceFeature>> features) {
    MHandle cur_mode;
    MInt32 cur_process_mask;
    bool have_compare_result = false;
    float threshold;
    ASF_CompareModel compareModel;

    if (detect_mode == DetectMode::IMAGE) {
        cur_mode = image_handle;
        cur_process_mask = image_process_mask;
        threshold = 0.82;
        compareModel = ASF_ID_PHOTO;
    } else if (detect_mode == DetectMode::VIDEO) {
        cur_mode = video_handle;
        cur_process_mask = video_process_mask;
        threshold = 0.80;
        compareModel = ASF_LIFE_PHOTO;
    } else {
        throw runtime_error("未知的初始化句柄?");
    }

    // ---对图像的裁剪，图像宽度需要四字节对齐（宽度为4的倍数)---
    auto originalImg = cvIplImage(frame);
    IplImage *img = cvCreateImage(cvSize(originalImg.width - originalImg.width %
                                                             4, originalImg.height), IPL_DEPTH_8U,
                                  originalImg.nChannels);
    CvSize size = cvSize(img->width, img->height);//区域大小
    cvSetImageROI(&originalImg, cvRect(0, 0, size.width, size.height));//设置源图像ROI
    cvCopy(&originalImg, img); //复制图像
    cvResetImageROI(&originalImg);//源图像用完后,清空ROI
    // --------------------------------------------------

    // 构造出的输入图像数据
    ASVLOFFSCREEN offscreen = {0};
    offscreen.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
    offscreen.i32Width = img->width;
    offscreen.i32Height = img->height;
    offscreen.pi32Pitch[0] = img->widthStep;
    offscreen.ppu8Plane[0] = (MUInt8 *) img->imageData;

    ASF_MultiFaceInfo detectedFaces = {0};

    MRESULT res = ASFDetectFacesEx(cur_mode, &offscreen, &detectedFaces);

    DetectFaceResult result;
    if (MOK != res) {
        std::cout << "detect faces fail" << std::endl;
    } else {
        // 打印人脸检测结果
        res = ASFProcessEx(cur_mode, &offscreen, &detectedFaces, cur_process_mask);
        if (res != MOK)
            std::cout << "process fail" << std::endl;

        // 遍历每个人脸
        for (int i = 0; i < detectedFaces.faceNum; i++) {
            string show_name;
            // 方框位置
            ASF_SingleFaceInfo singleDetectedFaces = {0};
            auto cur_face_rect_left = singleDetectedFaces.faceRect.left = detectedFaces.faceRect[i].left;
            auto cur_face_rect_top = singleDetectedFaces.faceRect.top = detectedFaces.faceRect[i].top;
            auto cur_face_rect_right = singleDetectedFaces.faceRect.right = detectedFaces.faceRect[i].right;
            auto cur_face_rect_bottom = singleDetectedFaces.faceRect.bottom = detectedFaces.faceRect[i].bottom;
            auto cur_face_rect_orient = singleDetectedFaces.faceOrient = detectedFaces.faceOrient[i];

            // 比对打开的话，需要特征比对
            if (is_compare) {
                // 获取当前脸的特征
                ASF_FaceFeature cur_feature = {0};

                MRESULT ExtractRes = ASFFaceFeatureExtractEx(cur_mode, &offscreen, &singleDetectedFaces,
                                                             &cur_feature);

                if (ExtractRes != MOK) {
                    std::cout << "current single face extract feature fail" << std::endl;
                    continue;
                }

                MFloat confidenceLevel;
                // 在遍历一次所有特征，并与当前检测到的特征进行比对
                for (auto db_feature: features) {
                    auto name = db_feature.first;
                    auto s_feature = db_feature.second;

                    auto CompareRes = ASFFaceFeatureCompare(cur_mode, &s_feature, &cur_feature,
                                                            &confidenceLevel, compareModel);
                    if (CompareRes != MOK) {
                        std::cout << "face feature compare fail" << std::endl;
                        continue;
                    }

                    // 设定一个默认阈值，0.8（也是官方推荐）
                    std::cout << "confidenceLevel: " << std::endl;
                    std::cout << confidenceLevel << std::endl;
                    if (confidenceLevel >= threshold) {
                        show_name = name;
                        have_compare_result = true;
                        break;
                    }
                }

            }

            // 年龄
            ASF_AgeInfo ageInfo = {0};
            res = ASFGetAge(cur_mode, &ageInfo);
            int age = 0;
            if (res == MOK) {
//                    printf("年龄:%d\n", ageInfo.ageArray[i]);
                age = ageInfo.ageArray[i];
            }
            // 性别
            ASF_GenderInfo genderInfo = {0};
            res = ASFGetGender(cur_mode, &genderInfo);
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

            // 绘制到frame:Mat上
            rectangle(frame, cv::Point(cur_face_rect_left, cur_face_rect_top),
                      cv::Point(cur_face_rect_right, cur_face_rect_bottom),
                      c, 1);

            // 人脸显示
            int theta = 15;

            // 年龄柱状显示
            auto dis = (cur_face_rect_right - cur_face_rect_left) / 10;
            for (int j = 1; j < int(age / 10) + 1; ++j) {
                cv::line(frame, cv::Point(dis * j + cur_face_rect_left, cur_face_rect_top),
                         cv::Point(dis * j + cur_face_rect_left, cur_face_rect_top - 5 * j),
                         cv::Scalar(0, 255, 255),
                         1);
            }

            // 其他显示
            int x_start = frame.cols - 200;
            int x_end = frame.cols - 140;
            int font_x = x_end + 5;
            int y = 20;

            // 提示信息显示
            cv::rectangle(frame, cv::Point(x_start - 10, y - 10), cv::Point(frame.cols - 5, y + 75),
                          cv::Scalar(0, 0, 0));


            cv::line(frame, cv::Point(x_start, y), cv::Point(x_end, y), cv::Scalar(255, 0, 0),
                     1);
            cv::putText(frame, "male", cv::Point(font_x, y + 5), 1, 1, cv::Scalar(255, 0, 0));


            cv::line(frame, cv::Point(x_start, y + 15), cv::Point(x_end, y + 15), cv::Scalar(0, 0, 255),
                     1);
            cv::putText(frame, "female", cv::Point(font_x, y + 15 + 5), 1, 1, cv::Scalar(0, 0, 255));

            cv::line(frame, cv::Point(x_start, y + 30), cv::Point(x_end, y + 30), cv::Scalar(0, 255, 0),
                     1);
            cv::putText(frame, "registered", cv::Point(font_x, y + 30 + 5), 1, 1, cv::Scalar(0, 255, 0));

            cv::line(frame, cv::Point(x_start, y + 45), cv::Point(x_end, y + 45), cv::Scalar(150, 150, 150),
                     1);
            cv::putText(frame, "not register", cv::Point(font_x, y + 45 + 5), 1, 1, cv::Scalar(150, 150, 150));

            cv::line(frame, cv::Point(x_start, y + 60), cv::Point(x_end, y + 60), cv::Scalar(0, 255, 255),
                     1);
            cv::putText(frame, "age", cv::Point(font_x, y + 60 + 5), 1, 1, cv::Scalar(0, 255, 255));

            if (is_compare & !show_name.empty()) {
                int baseline = 0;
                auto text_size = cv::getTextSize(show_name.data(), 1, 0.7, 1, &baseline);
                cv::rectangle(frame,
                              cv::Point(cur_face_rect_left + theta,
                                        cur_face_rect_top + theta - text_size.height - 2),
                              cv::Point(cur_face_rect_left + theta + text_size.width + 1,
                                        cur_face_rect_top + theta),
                              cv::Scalar(0, 255, 0),
                              -1);

                cv::putText(frame, show_name.data(),
                            cv::Point(cur_face_rect_left + theta + 1, cur_face_rect_top + theta - 1), 1,
                            0.7,
                            cv::Scalar(255, 255, 255));

                rectangle(frame,
                          cv::Point(cur_face_rect_left + theta, cur_face_rect_top + theta),
                          cv::Point(cur_face_rect_right - theta,
                                    cur_face_rect_bottom - theta),
                          cv::Scalar(0, 255, 0), 1);

//                cv::putText(frame, show_name, cv::Point(cur_face_rect_left, cur_face_rect_top - 10), 1, 1,
//                            cv::Scalar(0, 255, 255));
            } else {
                show_name = "not register";
                int baseline = 0;
                auto text_size = cv::getTextSize(show_name.data(), 1, 0.7, 1, &baseline);
                cv::rectangle(frame,
                              cv::Point(cur_face_rect_left + theta,
                                        cur_face_rect_top + theta - text_size.height - 2),
                              cv::Point(cur_face_rect_left + theta + text_size.width + 1,
                                        cur_face_rect_top + theta),
                              cv::Scalar(150, 150, 150),
                              -1);

                cv::putText(frame, show_name.data(),
                            cv::Point(cur_face_rect_left + theta + 1, cur_face_rect_top + theta - 1), 1,
                            0.7,
                            cv::Scalar(255, 255, 255));

                rectangle(frame,
                          cv::Point(cur_face_rect_left + theta, cur_face_rect_top + theta),
                          cv::Point(cur_face_rect_right - theta,
                                    cur_face_rect_bottom - theta),
                          cv::Scalar(150, 150, 150), 1);
            }
        }
    }
    //释放图像内存,这里只是做人脸检测,若还需要做特征提取等处理,图像数据没必要释放这么早
    cvReleaseImage(&img);

    result.flag = have_compare_result;
    result.detect_image = frame;

    return result;
}

/**
 * 单人脸-人脸特征提取，主要用于后续的人脸比对
 * @param frame
 * @return 是否提取成功,特征,成功/错误信息
 */
std::tuple<bool, ASF_FaceFeature, string, cv::Mat> ArcFace::face_features_extract(const cv::Mat &frame) {
    // ---对图像的裁剪，图像宽度需要四字节对齐（宽度为4的倍数)---
    auto originalImg = cvIplImage(frame);
    IplImage *img = cvCreateImage(cvSize(originalImg.width - originalImg.width %
                                                             4, originalImg.height), IPL_DEPTH_8U,
                                  originalImg.nChannels);
    CvSize size = cvSize(img->width, img->height);//区域大小
    cvSetImageROI(&originalImg, cvRect(0, 0, size.width, size.height));//设置源图像ROI
    cvCopy(&originalImg, img); //复制图像
    cvResetImageROI(&originalImg);//源图像用完后,清空ROI
    // --------------------------------------------------

    // 构造出的输入图像数据
    ASVLOFFSCREEN offscreen = {0};
    offscreen.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
    offscreen.i32Width = img->width;
    offscreen.i32Height = img->height;
    offscreen.pi32Pitch[0] = img->widthStep;
    offscreen.ppu8Plane[0] = (MUInt8 *) img->imageData;

    ASF_SingleFaceInfo singleDetectedFaces = {0};
    ASF_MultiFaceInfo multiFaces = {0};
    ASF_FaceFeature feature = {0};

    MRESULT res = ASFDetectFacesEx(image_handle, &offscreen, &multiFaces);

    if (res != MOK) {
        cvReleaseImage(&img);
        return std::make_tuple(false, feature, "人脸检测失败", cv::Mat());
    }

    if (multiFaces.faceNum != 1) {
        cvReleaseImage(&img);
        return std::make_tuple(false, feature, "检测到的人脸>1或=0", cv::Mat());
    }

    // 构造单人脸结构体
    singleDetectedFaces.faceRect.left = multiFaces.faceRect[0].left;
    singleDetectedFaces.faceRect.top = multiFaces.faceRect[0].top;
    singleDetectedFaces.faceRect.right = multiFaces.faceRect[0].right;
    singleDetectedFaces.faceRect.bottom = multiFaces.faceRect[0].bottom;
    singleDetectedFaces.faceOrient = multiFaces.faceOrient[0];

    MRESULT ExtractRes = ASFFaceFeatureExtractEx(image_handle, &offscreen, &singleDetectedFaces,
                                                 &feature);
    if (ExtractRes != MOK) {
        cvReleaseImage(&img);
        return std::make_tuple(false, feature, "人脸特征提取失败", cv::Mat());
    } else {
        cvReleaseImage(&img);
        cv::circle(frame, cv::Point((singleDetectedFaces.faceRect.right - singleDetectedFaces.faceRect.left) / 2 +
                                    singleDetectedFaces.faceRect.left,
                                    (singleDetectedFaces.faceRect.bottom - singleDetectedFaces.faceRect.top) / 2 +
                                    singleDetectedFaces.faceRect.top),
                   int((singleDetectedFaces.faceRect.bottom - singleDetectedFaces.faceRect.top) / 2),
                   cv::Scalar(0, 255, 0));

//        std::cout << "featureSize: " << std::endl;
//        std::cout << feature.featureSize << std::endl;
//        std::cout << "feature row: " << std::endl;
//        to_string(feature.feature);
//        char ch;
//        QChar qch(feature.feature);
//        ch = qch.to();
//        std::cout<<to_string(ch)<<std::endl;
//        QString((QChar(feature.feature)));
//        _f.decomposition();
//        std::cout<<feature.feature<<std::endl;

//        featureSize:
//        32678
//        feature row:
//        �

        return std::make_tuple(true, feature, "人脸特征提取成功", frame);
    }
}