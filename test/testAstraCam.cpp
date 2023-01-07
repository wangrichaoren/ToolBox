#include <opencv2/opencv.hpp>
#include "src/AstraCamera.hpp"
#include <iostream>


using namespace std;
//using namespace cv;


int main() {
    AstraCamera cam;
    cam.start(SteamMode::ALL);
    while (true) {
        cam.updateFrame();
        auto i = cam.getColorMat();
        auto d = cam.getDepthMat();
        imshow("test", i);
        imshow("test2", d);
        int k = cv::waitKey(30);
        if (k == 27) {
            break;
        } else if (k == 32) {
            imwrite("./rgb.png", i);
            imwrite("./depth.png", d);
        }

    }

};