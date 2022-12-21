cmake_minimum_required(VERSION 3.23)
project(ToolBox)

set(CMAKE_CXX_STANDARD 14)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lpthread -Wl,--no-as-needed  -g3 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

SET(COMMON_COMPILE_FLAGS "-fopenmp -Wall -Wno-sign-compare")
SET(CMAKE_CXX_FLAGS "${PLATFORM_COMPILE_FLAGS} ${COMMON_COMPILE_FLAGS} $ENV{CXXFLAGS}")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")

IF (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    SET(PLATFORM_COMPILE_FLAGS "-mfpu=neon")
ELSE ()
    SET(PLATFORM_COMPILE_FLAGS "-march=native")
    # some places of the algorithm are designed for 128 SIMD
    # so 128 SSE may slightly faster than 256 AVX, you may want this
    #    SET(PLATFORM_COMPILE_FLAGS "-msse -msse2 -msse3 -msse4 -mssse3")  # SSE only
ENDIF ()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
#message(STATUS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(OpenCV)
find_package(SFML COMPONENTS graphics window system)
# astra 相机驱动
find_package(Astra REQUIRED)

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

set(SOURCE src/main_window.cpp src/main_window.h src/main_window.ui src/encoder.cpp src/encoder.h src/encoder.ui src/utils.h src/utils.cpp src/DES.h src/DES.cpp src/myencoder.cpp src/myencoder.h src/admin_system.cpp src/admin_system.h src/admin_system.ui src/temple_match.cpp src/temple_match.h src/temple_match.ui src/imagewidget.cpp src/imagewidget.h src/face_detect.cpp src/face_detect.h src/face_detect.ui src/newImageWidget.cpp src/newImageWidget.h src/camera.cpp src/camera.h src/ArcFace.cpp src/ArcFace.h src/AstraCamera.h src/AstraCamera.cpp)
set(RESOURCES resources.qrc)
set(LIND2DUP src/line2Dup.cpp src/face_detect.cpp src/face_detect.h src/face_detect.ui)
set(YAMLCPP ${PROJECT_SOURCE_DIR}/3rdParty/lib/yaml-cpp/libyaml-cpp.a)
set(ARCSOFT_FACE "/home/wrc/Desktop/ToolBox/3rdParty/lib/arcsoft_face/libarcsoft_face.so" "/home/wrc/Desktop/ToolBox/3rdParty/lib/arcsoft_face/libarcsoft_face_engine.so")

#add_executable(ToolBox main.cpp ${SOURCE} ${RESOURCES} ${LIND2DUP})
add_executable(test test.cpp)

#target_link_libraries(ToolBox ${QT_LIBRARIES} ${OpenCV_LIBS} ${YAMLCPP} ${ARCSOFT_FACE} ${ASTRA_LIBRARIES})
message(${SFML_LIBRARIES})
target_link_libraries(test ${ARCSOFT_FACE} ${ASTRA_LIBRARIES} ${SFML_LIBRARIES})