//#include <opencv2/opencv.hpp>
//#include "src/AstraCamera.hpp"
//#include <iostream>
//
//
//using namespace std;
////using namespace cv;
//
//
//int main() {
//    int c = 0;
//    AstraCamera cam;
//    cam.start(SteamMode::ALL);
//    while (true) {
//        cam.updateFrame();
//        auto i = cam.getColorMat();
//        auto d = cam.getDepthMat();
//        imshow("test", i);
//        imshow("test2", d);
//        int k = cv::waitKey(30);
//        if (k == 27) {
//            break;
//        } else if (k == 32) {
////            string save_path = "/home/wrc/Desktop/camera/";
////            imwrite(save_path + to_string(c) + ".png", i);
////            c += 1;
////            d.convertTo(d, CV_16U);
//            imwrite("./color.png", i);
//            imwrite("./depth.tiff", d);
//
//        }
//
//    }
//
//};



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
#include <astra/astra/astra.hpp>
#include <cstdio>
#include <iostream>
#include <opencv2/opencv.hpp>
#include<pcl/io/pcd_io.h>
#include<pcl/io/ply_io.h>
#include<pcl/point_types.h>
#include<pcl/visualization/pcl_visualizer.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


class SampleFrameListener : public astra::FrameListener {
private:
    // 彩色
    using buffer_ptr = std::unique_ptr<astra::RgbPixel[]>;
    // 深度
    using dep_buffer_ptr = std::unique_ptr<int16_t[]>;

    buffer_ptr buffer_;
    dep_buffer_ptr dep_buffer_;
    unsigned int lastWidth_;
    unsigned int lastHeight_;
    unsigned int lastDeptWidth_;
    unsigned int lastDeptHeight_;
    Mat colorMat_;
    Mat depMat_;

public:

    Mat get_color_frame() {
        if (!colorMat_.empty()) {

            return colorMat_;
        }
    }

    Mat get_dep_frame() {
        if (!depMat_.empty()) {

            return depMat_;
        }
    }

    // 通过实现frame listener的on frame ready实现的
    virtual void on_frame_ready(astra::StreamReader &reader,
                                astra::Frame &frame) override {
        const astra::ColorFrame colorFrame = frame.get<astra::ColorFrame>();
        const astra::DepthFrame depthFrame = frame.get<astra::DepthFrame>();

        if (colorFrame.is_valid() && depthFrame.is_valid()) {
            // 获取彩色数据
            print_color(colorFrame);
            // 获取深度数据
            auto depthStream = reader.stream<astra::DepthStream>();
            print_depth(depthFrame, depthStream.coordinateMapper());
        }
    }

    void print_depth(const astra::DepthFrame &depthFrame,
                     const astra::CoordinateMapper &mapper) {
        if (depthFrame.is_valid()) {
            int width = depthFrame.width();
            int height = depthFrame.height();
            int frameIndex = depthFrame.frame_index();

            //determine if buffer needs to be reallocated
            if (width != lastDeptWidth_ || height != lastDeptHeight_) {
                dep_buffer_ = dep_buffer_ptr(new int16_t[depthFrame.length()]);
                lastDeptWidth_ = width;
                lastDeptHeight_ = height;
            }
            depthFrame.copy_to(dep_buffer_.get());
            // data type is uint8
            cv::Mat tmpMat(height, width, CV_16UC1, dep_buffer_.get());
            // mat类型的数据作为成员属性
            depMat_ = tmpMat;
//            cout << depMat_.at<uint16_t>(width / 2, height / 2) << endl;

            size_t index = ((width * (height / 2.0f)) + (width / 2.0f));
            short middle = dep_buffer_[index];
            cout << middle << endl;

            float worldX, worldY, worldZ;
            float depthX, depthY, depthZ;
            mapper.convert_depth_to_world(width / 2.0f, height / 2.0f, middle, worldX, worldY, worldZ);
            mapper.convert_world_to_depth(worldX, worldY, worldZ, depthX, depthY, depthZ);

            std::cout << "depth frameIndex: " << frameIndex
                      << " value: " << middle
                      << " wX: " << worldX
                      << " wY: " << worldY
                      << " wZ: " << worldZ
                      << " dX: " << depthX
                      << " dY: " << depthY
                      << " dZ: " << depthZ
                      << std::endl;
        }
    }


    void print_color(const astra::ColorFrame &colorFrame) {
        if (colorFrame.is_valid()) {
            int width = colorFrame.width();
            int height = colorFrame.height();
            auto frameIndex = colorFrame.frame_index();

            if (width != lastWidth_ || height != lastHeight_) {
                buffer_ = buffer_ptr(new astra::RgbPixel[colorFrame.length()]);
                lastWidth_ = width;
                lastHeight_ = height;
            }
            colorFrame.copy_to(buffer_.get());
            cv::Mat tmpMat(height, width, CV_8UC3, buffer_.get());
            cvtColor(tmpMat, tmpMat, COLOR_BGR2RGB);
            // mat类型的数据作为成员属性
            colorMat_ = tmpMat;

        }
    }
};

int main(int argc, char **argv) {
    astra::initialize();

    astra::StreamSet streamSet;
    astra::StreamReader reader = streamSet.create_reader();

    SampleFrameListener listener;


    // 彩色通道
    auto colorStream = reader.stream<astra::ColorStream>();
//    std::cout << typeid(&colorStream).name() << std::endl;
    colorStream.start();
    std::cout << "colorStream -- hFov: "
              << reader.stream<astra::ColorStream>().hFov()
              << " vFov: "
              << reader.stream<astra::ColorStream>().vFov()
              << std::endl;

    // 深度通道
    auto depthStream = reader.stream<astra::DepthStream>();
    depthStream.start();
//    depthStream.enable_registration(true);
    char serialnumber[256];
    depthStream.serial_number(serialnumber, 256);
    // 芯片id
    const uint32_t chipId = depthStream.chip_id();
    switch (chipId) {
        case ASTRA_CHIP_ID_MX400:
            std::cout << "Chip ID: MX400" << std::endl;
            break;
        case ASTRA_CHIP_ID_MX6000:
            std::cout << "Chip ID: MX6000" << std::endl;
            break;
        case ASTRA_CHIP_ID_UNKNOWN:
        default:
            std::cout << "Chip ID: Unknown" << std::endl;
            break;
    }
    const astra_usb_info_t usbinfo = depthStream.usb_info();
    std::cout << "usbInfo ---pid:" << usbinfo.pid << " vid: " << usbinfo.vid << std::endl;
    reader.add_listener(listener);

    cv::Mat cameraMatrix = cv::Mat_<double>(3, 3);
//    cv::FileStorage paramFs("./calib_bak1.yaml", cv::FileStorage::READ);
//    paramFs["K"] >> cameraMatrix;

    cv::FileStorage paramFs("../config/calib_bak1.yaml", cv::FileStorage::READ);
    paramFs["K"] >> cameraMatrix;
    // 内参数据
    double camera_fx = cameraMatrix.at<double>(0, 0);
    double camera_fy = cameraMatrix.at<double>(1, 1);
    double camera_cx = cameraMatrix.at<double>(0, 2);
    double camera_cy = cameraMatrix.at<double>(1, 2);

    std::cout << "camera_fx: " << camera_fx << std::endl;
    std::cout << "camera_fy: " << camera_fy << std::endl;
    std::cout << "camera_cx: " << camera_cx << std::endl;
    std::cout << "camera_cy: " << camera_cy << std::endl;

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));

    do {
        astra_update();
        Mat color = listener.get_color_frame();
        Mat depth = listener.get_dep_frame();

//        imshow("depth", depth);
//        imshow("color", color);

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>());
        // 遍历深度图
        for (int v = 0; v < depth.rows; v++)
            for (int u = 0; u < depth.cols; u++) {
                // 获取深度图中(m,n)处的值
                ushort d = depth.ptr<ushort>(v)[u];
                // d 可能没有值，若如此，跳过此点
                if (isnan(d) && abs(d) < 0.0001)
                    continue;
                // d 存在值，则向点云增加一个点
                pcl::PointXYZRGB p;

                // 计算这个点的空间坐标
                p.z = double(d) / 1000; //单位是米
                p.x = (u - camera_cx) * p.z / camera_fx;
                p.y = (v - camera_cy) * p.z / camera_fy;

                // 从rgb图像中获取它的颜色
                // rgb是三通道的BGR格式图，所以按下面的顺序获取颜色
                cv::Vec3b bgr = color.at<cv::Vec3b>(v, u);
                p.b = bgr[0];
                p.g = bgr[1];
                p.r = bgr[2];

                // 把p加入到点云中
                cloud->points.push_back(p);
                //cout << cloud->points.size() << endl;
            }
//        cloud->height = 1;
//        cloud->width = cloud->points.size();
//        cout << "point cloud size = " << cloud->points.size() << endl;
//        cloud->is_dense = false;
        viewer->removePointCloud("cloud");
        viewer->addPointCloud<pcl::PointXYZRGB>(cloud, "cloud");
        viewer->spinOnce();
        if (viewer->wasStopped()) {
            break;
        }


//        auto k = waitKey(30);
//        // q esc break
//        if (k == 113 | k == 27) {
//            break;
//        } else if (k == 32) {
////            printf("save color&depth img!");
//////            imwrite("./color.png", cmat);
//////            imwrite("./depth.diff", dmat);
////            cv::imwrite("./color.png", cmat);
////            cv::imwrite("./depth.tiff", dmat);
//        }

    } while (1);

    reader.remove_listener(listener);

    astra::terminate();
}