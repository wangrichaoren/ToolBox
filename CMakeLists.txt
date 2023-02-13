cmake_minimum_required(VERSION 3.23)
project(ToolBox)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_BUILD_TYPE "Release")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lpthread -Wl,--no-as-needed  -g3 -Wall -fPIC")

SET(COMMON_COMPILE_FLAGS "-fopenmp -Wall -Wno-sign-compare")

IF (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    SET(PLATFORM_COMPILE_FLAGS "-mfpu=neon")
ELSE ()
    SET(PLATFORM_COMPILE_FLAGS "-march=native")
ENDIF ()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

SET(CMAKE_CXX_FLAGS_RELEASE "${PLATFORM_COMPILE_FLAGS} ${COMMON_COMPILE_FLAGS} $ENV{CXXFLAGS}")

# qt相关
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(OpenCV 3 REQUIRED)
# eigen
include_directories("/usr/include/eigen3/")

# 导入astra相机驱动
find_package(Astra REQUIRED)
# ------导入pcl------
if (NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
    set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
endif ()
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
#message("pcl lib---"${PCL_LIBRARY_DIRS})
# ------------------

set(UI_SOURCE ${PROJECT_SOURCE_DIR}/src)
set(QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES})

include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${UI_SOURCE}
)

# include 3rdparty
#yaml-cpp lib
include_directories(${PROJECT_SOURCE_DIR}/3rdParty/include)
link_directories(${PROJECT_SOURCE_DIR}/3rdParty/lib)

# include MIPP headers
include_directories(${INCLUDE_DIRECTORIES} "3rdParty/include/MIPP/")

set(SOURCE
        src/encoder.cpp src/encoder.h src/encoder.ui src/utils.h src/utils.cpp src/DES.h src/DES.cpp
        src/myencoder.cpp src/myencoder.h src/temple_match.cpp src/temple_match.h src/temple_match.ui
        src/imagewidget.cpp src/imagewidget.h src/face_detect.cpp src/face_detect.h src/face_detect.ui
        src/newImageWidget.cpp src/newImageWidget.h src/camera.cpp src/camera.h src/ArcFace.cpp src/ArcFace.h
        src/AstraCamera.hpp src/calib.cpp src/calib.h src/calib.ui src/pcl_visual.cpp src/pcl_visual.h src/pcl_visual.ui
        src/start_window.cpp src/start_window.h src/start_window.ui src/local_camera.cpp src/local_camera.h src/base_camera.h
        )

set(RESOURCES resources.qrc)
set(LIND2DUP src/line2Dup.cpp)
set(YAMLCPP ${PROJECT_SOURCE_DIR}/3rdParty/lib/yaml-cpp/libyaml-cpp.a)
set(ARCSOFT_FACE ${PROJECT_SOURCE_DIR}/3rdParty/lib/arcsoft_face/libarcsoft_face.so ${PROJECT_SOURCE_DIR}/3rdParty/lib/arcsoft_face/libarcsoft_face_engine.so)

add_executable(ToolBox main.cpp ${SOURCE} ${RESOURCES} ${LIND2DUP})  # 主程序
#add_executable(test_local_cam test/test_local_cam.cpp src/local_camera.cpp src/local_camera.h src/base_camera.h)
#add_executable(test_camera_calib test/test_camera_calib.cpp)
add_executable(test_capture_images test/test_capture_images.cpp)
#add_executable(test_pcl test/test_pcl.cpp)
#add_executable(testAstraCam test/testAstraCam.cpp)

target_link_libraries(ToolBox ${QT_LIBRARIES} ${OpenCV_LIBS} ${YAMLCPP} ${ARCSOFT_FACE} ${ASTRA_LIBRARIES} ${PCL_LIBRARIES})
#target_link_libraries(test_local_cam ${OpenCV_LIBS})
#target_link_libraries(test_camera_calib ${OpenCV_LIBS} ${ASTRA_LIBRARIES})
target_link_libraries(test_capture_images ${OpenCV_LIBS} ${ASTRA_LIBRARIES})
#target_link_libraries(test_pcl  ${PCL_LIBRARIES} ${OpenCV_LIBS} ${ASTRA_LIBRARIES})
#target_link_libraries(testAstraCam  ${ASTRA_LIBRARIES} ${OpenCV_LIBS} ${PCL_LIBRARIES})

install(TARGETS ToolBox RUNTIME DESTINATION bin)