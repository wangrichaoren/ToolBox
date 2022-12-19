//
// Created by wrc on 22-12-6.
//

#ifndef TOOLBOX_UTILS_H
#define TOOLBOX_UTILS_H

#include <QBitmap>
#include <unistd.h>
#include <QLabel>
#include <iostream>
#include <sys/stat.h>
#include <QInputDialog>
#include <regex>


using namespace std;

/**
 * 设置widget背景
 * @param self
 * @param resource_path
 */
//void set_background(QWidget *self,const QString &resource_path){
//    self->setAutoFillBackground(true);
//    QPixmap bgImages(resource_path);
//    QPalette palette = self->palette();
//    palette.setBrush(QPalette::Background,
//                     QBrush(bgImages.scaled(  // 缩放背景图.
//                             self->size(),Qt::IgnoreAspectRatio,        //不限制原图片的长宽比
//                             Qt::SmoothTransformation)));               // 使用平滑的缩放方式
//    self->setPalette(palette);
//}

/**
 * 文件夹是否存在
 * @param folderpath
 * @return
 */
bool dirExists(const std::string &folderpath);

/**
 * 获取文件大小/其他信息
 * @param fileName
 * @return
 */
size_t getFileSize(const char *fileName);


/**
 * 设置label图案
 * @param label
 * @param file
 */
void setIconToLabel(QLabel *label, const QString &file);


void showMessageBox(QWidget *parent, const char *title);

void encrypt_file(const std::string &file_path);

void decrypt_file(const std::string &file_path, const std::string &key_path);

pair<bool, string> showInputBox(QWidget *parent, const char *title, const char *label);

vector<float> splitStringToFloat(string s);

vector<int> splitStringToInt(string s);

#endif //TOOLBOX_UTILS_H
