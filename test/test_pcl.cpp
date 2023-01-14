////
//// Created by wrc on 22-12-26.
////
//#include <iostream>
//#include <pcl/common/common_headers.h>
//#include <pcl/io/pcd_io.h>
//#include <pcl/visualization/pcl_visualizer.h>
//#include <pcl/visualization/cloud_viewer.h>
//#include <pcl/console/parse.h>
//using namespace std;
//
//int main(int argc, char **argv) {//柱型点云测试
//    cout << "Test PCL !" << endl;
//    pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_ptr (new pcl::PointCloud<pcl::PointXYZRGB>);
//    uint8_t r(255), g(15), b(15);
//    for (float z(-1.0); z <= 1.0; z += 0.05) {//制作柱型点云集
//        for (float angle(0.0); angle <= 360.0; angle += 5.0) {
//            pcl::PointXYZRGB point;
//            point.x = cos (pcl::deg2rad(angle));
//            point.y = sin (pcl::deg2rad(angle));
//            point.z = z;
//            uint32_t rgb = (static_cast<uint32_t>(r) << 16 | static_cast<uint32_t>(g) << 8 | static_cast<uint32_t>(b));
//            point.rgb = *reinterpret_cast<float*>(&rgb);
//            point_cloud_ptr->points.push_back (point);
//        }
//        if (z < 0.0) {//颜色渐变
//            r -= 12;
//            g += 12;
//        }
//        else {
//            g -= 12;
//            b += 12;
//        }
//    }
//
//    point_cloud_ptr->width = (int) point_cloud_ptr->points.size ();
//    point_cloud_ptr->height = 1;
//
//    pcl::visualization::CloudViewer viewer ("pcl test");
//
//    viewer.showCloud(point_cloud_ptr);
//    while (!viewer.wasStopped()){ };
//    return 0;
//}


/**以下为测试深度和rgb生成点云用例**/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <opencv2/imgproc.hpp>

using namespace std;

int main(int argc, char **argv) {
    // 数据读取
    cv::Mat rgb, depth;
    rgb = cv::imread("/home/wrc/Desktop/capture_datas/0_color.png", -1);
    depth = cv::imread("/home/wrc/Desktop/capture_datas/0_depth.png", -1);

//    cv::Rect rect(140, 100, 189 - 140, 177 - 100);
//    cv::rectangle(rgb, rect, cv::Scalar(255, 0, 0));
//    cv::rectangle(depth, rect, cv::Scalar(255, 0, 0));

//     left top - 285 212
//     right down - 311 283  189 177
//    rgb = rgb(rect);
//    depth = depth(rect);
//

//    cv::imwrite("/home/wrc/Desktop/capture_datas/rect_color.png", rgb);
//    cv::imwrite("/home/wrc/Desktop/capture_datas/rect_depth.png", depth);

//    cv::imshow("rect", image_ori);
//    while (1) {
//        int k = cv::waitKey();
//        if (k == 27) {
//            break;
//        }
//    }

//    cv::waitKey(300);

    // 相机内参与缩放系数
//    double cx = 3.1348380900698828e+02; //313
//    double cy = 2.4305617964195247e+02; //243
    double cx = 310.24326;
    double cy = 253.65539;
    double fx = 577.54679;
    double fy = 578.63325;
    double depthScale = 1.0;

    // 定义点云使用的格式：这里用的是XYZRGB
    typedef pcl::PointXYZRGB PointT;
    typedef pcl::PointCloud<PointT> PointCloud;

    // 计算每个点对应的XYZRGB值
    PointCloud::Ptr pointCloud(new PointCloud);
    for (int v = 0; v < rgb.rows; v++)
        for (int u = 0; u < rgb.cols; u++) {
            unsigned int d = depth.ptr<unsigned short>(v)[u];
            if (d == 0)
                continue;
            PointT p;
            p.z = double(d) / depthScale;
            p.x = (u - cx) * p.z / fx;
            p.y = (v - cy) * p.z / fy;
            p.b = rgb.data[v * rgb.step + u * rgb.channels()];
            p.g = rgb.data[v * rgb.step + u * rgb.channels() + 1];
            p.r = rgb.data[v * rgb.step + u * rgb.channels() + 2];
            pointCloud->points.push_back(p);
        }

    // 点云保存
    pointCloud->is_dense = false;
    cout << "点云共有" << pointCloud->size() << "个点." << endl;
    pcl::io::savePCDFileBinary("/home/wrc/Desktop/capture_datas/cabin.pcd", *pointCloud);
    return 0;
}


//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <sstream>
//#include <cstdlib>
//#include <pcl/io/io.h>
//#include <pcl/io/pcd_io.h>
//
//
//using namespace std;
//using namespace cv;
//
///**
//     * 将彩色图和深度图合并成点云
//     * @param matrix 相机内参矩阵3x3
//     * @param rgb    彩色图
//     * @param depth  深度图
//     * @param cloud  输出点云
//     */
//static void convert(Mat &rgb, Mat &depth, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud) {
//    Mat cameraMatrix = cv::Mat_<double>(3, 3);
////    FileStorage paramFs("../config/calib_bak1.yaml", FileStorage::READ);
//    FileStorage paramFs("./calib_bak1.yaml", FileStorage::READ);
//    paramFs["K"] >> cameraMatrix;
//    // 内参数据
//    double camera_fx = cameraMatrix.at<double>(0, 0);
//    double camera_fy = cameraMatrix.at<double>(1, 1);
//    double camera_cx = cameraMatrix.at<double>(0, 2);
//    double camera_cy = cameraMatrix.at<double>(1, 2);
//
////    double camera_fx = matrix.at<double>(0, 0);
////    double camera_fy = matrix.at<double>(1, 1);
////    double camera_cx = matrix.at<double>(0, 2);
////    double camera_cy = matrix.at<double>(1, 2);
//
//
//    cout << "fx: " << camera_fx << endl;
//    cout << "fy: " << camera_fy << endl;
//    cout << "cx: " << camera_cx << endl;
//    cout << "cy: " << camera_cy << endl;
//
//    // 遍历深度图
//    for (int v = 0; v < depth.rows; v++)
//        for (int u = 0; u < depth.cols; u++) {
//            // 获取深度图中(m,n)处的值
//            ushort d = depth.ptr<ushort>(v)[u];
//            // d 可能没有值，若如此，跳过此点
//            if (isnan(d) && abs(d) < 0.0001)
//                continue;
//            // d 存在值，则向点云增加一个点
//            pcl::PointXYZRGB p;
//
//            // 计算这个点的空间坐标
//            p.z = double(d) / 1000; //单位是米
//            p.x = (u - camera_cx) * p.z / camera_fx;
//            p.y = (v - camera_cy) * p.z / camera_fy;
//
//            // 从rgb图像中获取它的颜色
//            // rgb是三通道的BGR格式图，所以按下面的顺序获取颜色
//            Vec3b bgr = rgb.at<Vec3b>(v, u);
//            p.b = bgr[0];
//            p.g = bgr[1];
//            p.r = bgr[2];
//
//            // 把p加入到点云中
//            cloud->points.push_back(p);
//            //cout << cloud->points.size() << endl;
//        }
//
//
//    // 设置并保存点云
//    cloud->height = 1;
//    cloud->width = cloud->points.size();
//    cout << "point cloud size = " << cloud->points.size() << endl;
//    cloud->is_dense = false;
//}
//
//int main() {
////    cv::Mat cameraMatrix = cv::imread("../config/calib_bak1.yaml"); // 从文件加载相机内参
//    cv::Mat rgb = cv::imread("./rgb.png", IMREAD_UNCHANGED);         // 从相机得到RGB彩色图
//    cv::Mat depth = cv::imread("./depth.tiff", IMREAD_UNCHANGED);       // 从相机得到depth深度图
////    imshow("depth", depth);
////    waitKey(255);
//    pcl::PointCloud<pcl::PointXYZRGB>::Ptr pCloud(new pcl::PointCloud<pcl::PointXYZRGB>());
//    convert(rgb, depth, pCloud);
//    pcl::PCDWriter writer;
//    writer.write("./cloud.pcd", *pCloud);
//};




//float qnan_ = std::numeric_limits<float>::quiet_NaN();
//const char *cameraInCailFile = "../config/calib_bak1.yaml";
//
//Eigen::Matrix<float, 640, 1> colmap;
//Eigen::Matrix<float, 480, 1> rowmap;
////const short w = 512, h = 424;
//const short w = 640, h = 480;
//
//void prepareMake3D(const double cx, const double cy,
//                   const double fx, const double fy) {
//    float *pm1 = colmap.data();
//    float *pm2 = rowmap.data();
//    for (int i = 0; i < w; i++) {
//        *pm1++ = (i - cx + 0.5) / fx;
//    }
//    for (int i = 0; i < h; i++) {
//        *pm2++ = (i - cy + 0.5) / fy;
//    }
//}
//
///**
// * 根据内参，合并RGB彩色图和深度图到点云
// * @param cloud
// * @param depthMat
// * @param rgbMat
// */
//void getCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud, Mat &depthMat, Mat &rgbMat) {
//    const float *itD0 = (float *) depthMat.ptr();
//    const char *itRGB0 = (char *) rgbMat.ptr();
//
//    if (cloud->size() != w * h)
//        cloud->resize(w * h);
//
//    std::cout << "debug 1" << std::endl;
//    pcl::PointXYZRGB *itP = &cloud->points[0];
//    bool is_dense = true;
//    std::cout << "debug 2" << std::endl;
//
//    for (size_t y = 0; y < h; ++y) {
//
//        const unsigned int offset = y * w;
//        const float *itD = itD0 + offset;
//        const char *itRGB = itRGB0 + offset * 4;
//        const float dy = rowmap(y);
//
//        for (size_t x = 0; x < w; ++x, ++itP, ++itD, itRGB += 4) {
//            const float depth_value = *itD / 1000.0f;
//
//            if (!isnan(depth_value) && abs(depth_value) >= 0.0001) {
//
//                const float rx = colmap(x) * depth_value;
//                const float ry = dy * depth_value;
//                itP->z = depth_value;
//                itP->x = rx;
//                itP->y = ry;
//
//                itP->b = itRGB[0];
//                itP->g = itRGB[1];
//                itP->r = itRGB[2];
//            } else {
//                itP->z = qnan_;
//                itP->x = qnan_;
//                itP->y = qnan_;
//
//                itP->b = qnan_;
//                itP->g = qnan_;
//                itP->r = qnan_;
//                is_dense = false;
//            }
//        }
//    }
//    std::cout << "debug 4" << std::endl;
//    cloud->is_dense = is_dense;
//    std::cout << "生成ok了" << std::endl;
//}
//
//int main() {
//    Mat cameraMatrix = cv::Mat_<double>(3, 3);
//    FileStorage paramFs(cameraInCailFile, FileStorage::READ);
//    paramFs["CameraMatrix"] >> cameraMatrix;
//    // 内参数据
//    double fx = cameraMatrix.at<double>(0, 0);
//    double fy = cameraMatrix.at<double>(1, 1);
//    double cx = cameraMatrix.at<double>(0, 2);
//    double cy = cameraMatrix.at<double>(1, 2);
//    // 提前准备计算所需参数
//    prepareMake3D(cx, cy, fx, fy);
//    std::cout << "3d marker ok" << std::endl;
//    std::cout << fx << std::endl;
//    std::cout << fy << std::endl;
//    std::cout << cx << std::endl;
//    std::cout << cy << std::endl;
////    cv::Mat rgbMat;      // 从相机得到RGB彩色图
////    cv::Mat depthMat;        // 从相机得到depth深度图
//    cv::Mat rgbMat = cv::imread("./rgb.png");
//    cv::Mat depthMat = cv::imread("./depth.png", IMREAD_UNCHANGED);        // 从相机得到depth深度图
//    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>());
//    std::cout << "ready ok!" << std::endl;
//    getCloud(cloud, depthMat, rgbMat);
//}


//#include <opencv2/opencv.hpp>
//#include <opencv2/calib3d/calib3d.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <stdio.h>
//#include <iostream>
//
////定义标定板内角点维数
//int CHESSBOARD[2] = {5, 8};//纵向6个角点，横向9个角点
//using namespace std;
//using namespace cv;
//
//Rect validROIL, validROIR;
//Mat R, T, E, F; //R 旋转矢量 T平移矢量 E本征矩阵 F基础矩阵
//Mat Rl, Rr, Pl, Pr, Q;//校正旋转矩阵R，投影矩阵P 重投影矩阵Q (下面有具体的含义解释）
//cv::Mat R_cameraMatrix, R_distCoeffs, R_R, R_T;
//cv::Mat L_cameraMatrix, L_distCoeffs, L_R, L_T;
//Mat R_src, R_img, L_src, L_img, R_dst, L_dst;//图像
//double fx;
//
//void outputCameraParam(void) {
//    /*保存数据*/
//    /*输出数据*/
//    fx = R_cameraMatrix.at<double>(0, 0);
//    FileStorage fs("calib_bak1.yaml", FileStorage::WRITE);
//    if (fs.isOpened()) {
//        // 公共参数
//        fs << "CameraType" << "\"PinHole\"";
//        fs << "fx" << R_cameraMatrix.at<double>(0, 0);//.at()先行后列 (00)
//        fs << "fy" << R_cameraMatrix.at<double>(1, 1);//11
//        fs << "cx" << R_cameraMatrix.at<double>(0, 2);//02
//        fs << "cy" << R_cameraMatrix.at<double>(1, 2);//12
//        fs << "K" << R_cameraMatrix;
//        fs << "D" << R_distCoeffs;
//        fs.release();
//    } else
//        cout << "Error: 无法保存！\n";
//    cout << "参数已经写入至：calib_bak1.yaml！" << endl;
//    cout << "快开始下一步工作吧~再见:)" << endl;
//}
//
//
//int main() {
//    //////// 标定数据集的导入 //////////
//    //单目输入
//    vector<String> image_paths;//数据集中图像的路径
//    string path = "/home/wrc/Desktop/camera";//图像名称格式
//    glob(path, image_paths);// 将所有符合格式的图像路径存储到image_paths中
//
//    ////// 世界坐标系三维坐标输入 //////
//    vector<Point3f> objp; // 存储关键点在真实世界中的三维坐标
//    for (int i = 0; i < CHESSBOARD[1]; i++) {
//        for (int j = 0; j < CHESSBOARD[0]; j++)
//            objp.push_back(Point3f(i * 27 * 0.01, j * 27 * 0.01, 0));//逐行标记内角点坐标
//    }
//
//
//    vector<Point2f> corners;
//    bool found1;
//    vector<vector<Point3f>> objPoints;//为整个数据集创建其在真实世界的三维坐标集合。
//    vector<vector<Point2f>> imgPoints;//图像上的关键点坐标位置
//    ///////// 遍历数据集 && 确定关键点位置 ///////////
//    std::cout << "正在搜索标定点……" << endl;
//    for (int i = 0; i < image_paths.size(); i++) {
//        R_src = imread(image_paths[i]);
//        cvtColor(R_src, R_img, COLOR_BGR2GRAY);
//        //寻找关键点位置
//        found1 = findChessboardCorners(R_img,
//                                       Size(CHESSBOARD[0], CHESSBOARD[1]), corners,
//                                       CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);
//        if (found1)//在图像上确定出内角点信息
//        {
//            TermCriteria criteria(2 | 1, 30, 0.001);//设置最大迭代次数与迭代终止条件
//            //使用亚像素精准化关键点坐标位置
//            cornerSubPix(R_img, corners, cv::Size(11, 11), cv::Size(-1, -1), criteria);
//            //在图像上显示检测到的关键点
//            //drawChessboardCorners(R_src, cv::Size(6, 9), corners, found1);
//            //存储关键点信息
//            objPoints.push_back(objp);
//            imgPoints.push_back(corners);
//        }
//        //cv::imshow("Corner Detected Right", R_src);//展示图像
//        //waitKey(0);
//    }
//    cv::destroyAllWindows();
//    cout << "标定点搜索完成！" << endl << endl << endl;
//
//    ////////// 计算相机内外参数 ///////////
//    cout << "开始计算镜头内外参，请稍等……" << endl;
//    cv::calibrateCamera(objPoints, imgPoints, cv::Size(R_img.rows, R_img.cols), R_cameraMatrix, R_distCoeffs, R_R,
//                        R_T); // LEFT.K LEFT.D
//    cout << "镜头内外参计算完成！" << endl;
//
//    outputCameraParam();//参数写入
//    Mat mapRx, mapRy;
//    //Mat new_camera_matrix,frame,dst;
//    //frame = imread("./data_new/left/L_1.jpg");
//    //initUndistortRectifyMap(L_cameraMatrix, L_distCoeffs, Rl, Pl, imageSize, CV_32FC1, mapLx, mapLy);
//    //remap(frame, dst, mapLx, mapLy, INTER_LINEAR);
//    //imshow("left undistort",dst);
//    //imshow("handwrite",handwrite_Undistort(frame));
//    //imshow("stereo calibrate",show_stereoCalib());
//    Mat srcR = imread("/home/wrc/Desktop/camera/0.png");
//    cv::Size imageSize(cv::Size(srcR.cols, srcR.rows));
//    initUndistortRectifyMap(R_cameraMatrix, R_distCoeffs, Rr, R_cameraMatrix, imageSize, CV_32FC1, mapRx, mapRy);
//    Mat rectifyImageR;
//    remap(srcR, rectifyImageR, mapRx, mapRy, INTER_LINEAR);
//    imshow("right undistort", rectifyImageR);
//    waitKey(0);
//    return 0;
//}


//#include <opencv2/opencv.hpp>
//#include "src/AstraCamera.hpp"
//#include<pcl/io/pcd_io.h>
//#include<pcl/io/ply_io.h>
//#include<pcl/point_types.h>
//#include<pcl/visualization/pcl_visualizer.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
////#include <pcl/point_types.h>
////#include <pcl/io/pcd_io.h>
//
//int main() {
//    AstraCamera cam;
//    cam.start(SteamMode::ALL);
//
//    // point cloud visual
//    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
//
//    cv::Mat cameraMatrix = cv::Mat_<double>(3, 3);
////    FileStorage paramFs("../config/calib_bak1.yaml", FileStorage::READ);
//    cv::FileStorage paramFs("../config/calib_bak1.yaml", cv::FileStorage::READ);
//    paramFs["K"] >> cameraMatrix;
//    // 内参数据
//    double camera_fx = cameraMatrix.at<double>(0, 0);
//    double camera_fy = cameraMatrix.at<double>(1, 1);
//    double camera_cx = cameraMatrix.at<double>(0, 2);
//    double camera_cy = cameraMatrix.at<double>(1, 2);
//
//    std::cout << "camera_fx: " << camera_fx << std::endl;
//    std::cout << "camera_fy: " << camera_fy << std::endl;
//    std::cout << "camera_cx: " << camera_cx << std::endl;
//    std::cout << "camera_cy: " << camera_cy << std::endl;
//
//    while (true) {
//        cam.updateFrame();
//        auto color = cam.getColorMat();
//        auto depth = cam.getDepthMat();
//        imshow("color", color);
//        imshow("depth", depth);
//
//        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>());
//        // 遍历深度图
//        for (int v = 0; v < depth.rows; v++)
//            for (int u = 0; u < depth.cols; u++) {
//                // 获取深度图中(m,n)处的值
//                ushort d = depth.ptr<ushort>(v)[u];
//                // d 可能没有值，若如此，跳过此点
//                if (isnan(d) && abs(d) < 0.0001)
//                    continue;
//                // d 存在值，则向点云增加一个点
//                pcl::PointXYZRGB p;
//
//                // 计算这个点的空间坐标
//                p.z = double(d) / 1000; //单位是米
//                p.x = (u - camera_cx) * p.z / camera_fx;
//                p.y = (v - camera_cy) * p.z / camera_fy;
//
//                // 从rgb图像中获取它的颜色
//                // rgb是三通道的BGR格式图，所以按下面的顺序获取颜色
//                cv::Vec3b bgr = color.at<cv::Vec3b>(v, u);
//                p.b = bgr[0];
//                p.g = bgr[1];
//                p.r = bgr[2];
//
//                // 把p加入到点云中
//                cloud->points.push_back(p);
//                //cout << cloud->points.size() << endl;
//            }
//        cloud->height = 1;
//        cloud->width = cloud->points.size();
//        cout << "point cloud size = " << cloud->points.size() << endl;
//        cloud->is_dense = false;
//        viewer->removePointCloud("cloud");
//        viewer->addPointCloud<pcl::PointXYZRGB>(cloud, "cloud");
//        viewer->spinOnce();
//
//        int k = cv::waitKey(30);
//        if (k == 27) {
//            break;
//        }
//    }
//}