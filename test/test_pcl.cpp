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

using namespace std;

int main(int argc, char **argv) {
    // 数据读取
    cv::Mat rgb, depth;
    rgb = cv::imread("./rgb.png");
    depth = cv::imread("./depth.png", -1);

//    double cx = 3.1950001165359771e+02;
//    double cy = 2.3949993846027792e+02;
//    double fx = 8.7152157967372148e+01;
//    double fy = 3.5072846783706171e+02;
//    double depthScale = 1.0;

    // 相机内参与缩放系数
    double cx = 3.1950052580389416e+02;
    double cy = 2.3950196646754412e+02;
    double fx = 1.1118634196120907e+02;
    double fy = 1.5096567808768597e+02;
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
    pcl::io::savePCDFileBinary("./cabinet.pcd", *pointCloud);
    return 0;
}