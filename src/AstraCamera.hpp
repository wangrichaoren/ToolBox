#include <astra/astra/capi/astra.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "astra/astra_core/capi/astra_core.h"
#include <unistd.h>
#include "base_camera.h"

#ifndef _ASTRA_CAMERA_
#define _ASTRA_CAMERA_

class AstraCamera : public BaseCamera {
private:
    astra_reader_t reader;
    astra_streamsetconnection_t sensor;
    astra_frame_index_t lastFrameIndex = -1;

    astra_depthstream_t colorStream;
    astra_depthstream_t depthStream;

    bool isPause = false;

    bool isRGB = false;
    bool isDepth = false;

    cv::Mat cMat;
    cv::Mat dMat;

public:

    AstraCamera() {
        astra_initialize();

        astra_streamset_open("device/default", &sensor);

        astra_reader_create(sensor, &reader);

        //*** rgb
        astra_reader_get_colorstream(reader, &colorStream);

        //*** depth
        astra_reader_get_depthstream(reader, &depthStream);
        astra_depthstream_set_registration(depthStream, true);
//        bool ok;
//        astra_depthstream_get_registration(depthStream, &ok);
//        std::cout << "astra_depthstream_get_registration: " << ok << std::endl;

        char serialnumber[256];
        astra_depthstream_get_serialnumber(depthStream, serialnumber, 256);
    }

    void registration(bool f) {
        astra_depthstream_set_registration(depthStream, f);
        bool ok;
        astra_depthstream_get_registration(depthStream, &ok);
//        astra_depthstream_set_d2c_resolution(depthStream,)
        std::cout << "astra_depthstream_get_registration: " << ok << std::endl;
    }

    ~AstraCamera() override {
        this->close();
//        astra_reader_destroy(&reader);
//        astra_streamset_close(&sensor);
//        astra_terminate();
        std::cout << "关闭ASTRA CAMERA!" << std::endl;
    }

    void close() override {
        astra_reader_destroy(&reader);
        astra_streamset_close(&sensor);
        astra_terminate();
    }

    void start(SteamMode e) override {
        if (e == ALL) {
            astra_stream_start(colorStream);
            astra_stream_start(depthStream);
            isRGB = true;
            isDepth = true;
        } else if (e == RGB) {
            astra_stream_start(colorStream);
            isRGB = true;
        } else if (e == DEPTH) {
            astra_stream_start(depthStream);
            isDepth = true;
        }
    }

    void stop() {
        astra_stream_stop(colorStream);
        astra_stream_stop(depthStream);
        isRGB = false;
        isDepth = false;
    }

    void pause(bool f) override {
        isPause = f;
//        isPause = !isPause;
    }

    bool checkOpen() override {
        bool is_alive = false;
        astra_streamset_is_available(sensor, &is_alive);
//        std::cout << "astra alive: " << is_alive << std::endl;
        return is_alive;
//        if ((isRGB + isDepth) == 0) {
//            return false;
//        }
//        return true;
    }

    void updateFrame() override {
        if (!checkOpen()) {
            throw std::runtime_error("astra link error!");
        }
        if ((isRGB + isDepth) == 0) {
            throw std::runtime_error("相机请先start，在update frame!");
        }

        if (isPause) {
            return;
        }

        astra_update();

        astra_reader_frame_t frame;
        astra_status_t rc = astra_reader_open_frame(reader, 0, &frame);
        if (rc == ASTRA_STATUS_SUCCESS) {
            astra_frame_index_t newFrameIndex;

            if (isRGB) {
                astra_colorframe_t colorFrame;
                astra_frame_get_colorframe(frame, &colorFrame);
                print_color(colorFrame);
                astra_colorframe_get_frameindex(colorFrame, &newFrameIndex);
            }

            if (isDepth) {
                astra_depthframe_t depthFrame;
                astra_frame_get_depthframe(frame, &depthFrame);
                print_depth(depthFrame);
                astra_depthframe_get_frameindex(depthFrame, &newFrameIndex);
            }

            if (lastFrameIndex == newFrameIndex) {
                printf("duplicate frame index: %d\n", lastFrameIndex);
            }
            lastFrameIndex = newFrameIndex;

            astra_reader_close_frame(&frame);
        } else {
            updateFrame();
        }
    };


    inline void print_color(astra_colorframe_t colorFrame) {
        astra_image_metadata_t metadata;
        astra_rgb_pixel_t *colorData_rgb;

        uint32_t colorByteLength;

        astra_colorframe_get_data_rgb_ptr(colorFrame, &colorData_rgb, &colorByteLength);

        astra_colorframe_get_metadata(colorFrame, &metadata);

        int width = metadata.width;
        int height = metadata.height;

        cv::Mat tmpMat(height, width, CV_8UC3, colorData_rgb);
        cvtColor(tmpMat, tmpMat, cv::COLOR_BGR2RGB);

        if (!tmpMat.empty()) {
            cMat = tmpMat;
//            tmpMat.release();
        }
    };

    inline void print_depth(astra_depthframe_t depthFrame) {
        astra_image_metadata_t metadata;

        int16_t *depthData;
        uint32_t depthLength;

        astra_depthframe_get_data_byte_length(depthFrame, &depthLength);
        astra_depthframe_get_metadata(depthFrame, &metadata);

        depthData = (int16_t *) malloc(depthLength);
        astra_depthframe_copy_data(depthFrame, depthData);

        int width = metadata.width;
        int height = metadata.height;

        cv::Mat tmpMat(height, width, CV_16UC1, depthData);
        // 在free掉数组指针前，copy一份Mat，否则深度信息拿到的有问题
        cv::Mat dst;
        tmpMat.copyTo(dst);

        free(depthData);

        if (!dst.empty()) {
            dMat = dst;
        }
    }

    cv::Mat getColorMat() override {
        return cMat;
    }

    inline cv::Mat getDepthMat() {
        return dMat;
    }

};

#endif //_ASTRA_CAMERA_