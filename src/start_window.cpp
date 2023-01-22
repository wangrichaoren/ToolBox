//
// Created by wrc on 23-1-22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_start_window.h" resolved

#include "start_window.h"
#include <QDesktopWidget>
#include <iostream>
#include "utils.h"
#include "ui_start_window.h"
#include "encoder.h"
#include "temple_match.h"
#include "calib.h"
#include "face_detect.h"
#include "pcl_visual.h"


start_window::start_window(QWidget *parent) :
        QWidget(parent), ui(new Ui::start_window) {
    ui->setupUi(this);
    // 移动至画面中心
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);

    // 图标
    auto p = get_abs_path("../icons/image0.jpg");
    this->setWindowIcon(QIcon(p.data()));

    ui->file_encryption_btn->setToolTip("用于文件加密/解密的小工具，加解密算法采用AES");
    ui->match_btn->setToolTip("基于形状边缘特征匹配的小工具,shape base matching");
    ui->cam_calib_btn->setToolTip("用于标定相机内参小工具");
    ui->face_det_btn->setToolTip("人脸识别小工具");
    ui->pc_visual_btn->setToolTip("点云离线/在线查看小工具");
    ui->exit_btn->setToolTip("退出");

    // 加解密
    connect(ui->file_encryption_btn, &QPushButton::clicked, [=] {
        this->setEnabled(false);
        auto e = new encoder();
        e->show();
        e->exec();
        e->deleteLater();
        this->setEnabled(true);
    });

    // 模板匹配
    connect(ui->match_btn, &QPushButton::clicked, [=] {
        this->setEnabled(false);
        auto t_m = new temple_match();
        t_m->show();
        t_m->exec();
        t_m->deleteLater();
        this->setEnabled(true);
    });

    // 相机标定
    connect(ui->cam_calib_btn, &QPushButton::clicked, [=] {
        this->setEnabled(false);
        auto c = new calib();
        c->show();
        c->exec();
        c->deleteLater();
        this->setEnabled(true);
    });

    // 人脸识别
    connect(ui->face_det_btn, &QPushButton::clicked, [=] {
        this->setEnabled(false);
        auto f_d = new face_detect();
        f_d->show();
        f_d->exec();
        f_d->deleteLater();
        this->setEnabled(true);
    });

    // 点云查看器
    connect(ui->pc_visual_btn, &QPushButton::clicked, [=] {
        this->setEnabled(false);
        auto p_v = new pcl_visual();
        p_v->show();
        p_v->exec();
        p_v->deleteLater();
        this->setEnabled(true);
    });

    // todo 未完成
    connect(ui->pushButton, &QPushButton::clicked, [=] {
        showMessageBox(this, "未开发的功能...");
        return;
    });

    // 退出
    connect(ui->exit_btn, &QPushButton::clicked, [=] {
        this->close();
    });

}

start_window::~start_window() {
    delete ui;
    std::cout << "关闭窗口" << std::endl;
}
