//
// Created by wrc on 22-12-21.
//

#ifndef TOOLBOX_ASTRACAMERA_H
#define TOOLBOX_ASTRACAMERA_H

#include <astra/astra_core/astra_core.hpp>
#include <astra/astra/astra.hpp>
#include <astra/LitDepthVisualizer.hpp>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <astra/key_handler.h>


enum ColorMode {
    MODE_COLOR,
    MODE_IR_16,
    MODE_IR_RGB
};


class AstraCamera {
public:
    AstraCamera();

    ~AstraCamera();

private:
    astra::DepthStream configure_depth(astra::StreamReader &reader);

    astra::ColorStream configure_color(astra::StreamReader &reader);

    astra::InfraredStream configure_ir(astra::StreamReader &reader, bool useRGB);

};


#endif //TOOLBOX_ASTRACAMERA_H
