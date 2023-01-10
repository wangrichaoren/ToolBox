//
// Created by wrc on 22-12-8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_admin_system.h" resolved

#include "admin_system.h"
#include "ui_admin_system.h"
#include "utils.h"
#include "temple_match.h"
#include "face_detect.h"
#include "calib.h"
#include "pcl_visual.h"


admin_system::admin_system(QWidget *parent) :
        QDialog(parent), ui(new Ui::admin_system) {
    ui->setupUi(this);
    setIconToLabel(ui->label_1, ":/icons/星空.png");
    setIconToLabel(ui->label_2, ":/icons/沙滩.png");
    setIconToLabel(ui->label_3, ":/icons/秋天.png");
    setIconToLabel(ui->label_4, ":/icons/瀑布.png");

//    connect(ui->pushButton_1,)
    connect(ui->pushButton_1, &QPushButton::clicked, this, &admin_system::clickTempleMatchBtn);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &admin_system::clickFaceDetBtn);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &admin_system::clickCalibBtn);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &admin_system::clickPCLBtn);
}

admin_system::~admin_system() {
    delete ui;
}

void admin_system::clickTempleMatchBtn() {
    qDebug("打开模板匹配窗口");
    this->setEnabled(false);
    auto tm = new temple_match(this);
    tm->show();
    tm->exec();
    cout << "exec templates match" << endl;
    delete tm;
    this->setEnabled(true);
}

void admin_system::clickFaceDetBtn() {
    qDebug("打开人脸识别窗口");
    this->setEnabled(false);
    auto fd = new face_detect(this);
    fd->show();
    fd->exec();
    delete fd;
    this->setEnabled(true);
}

void admin_system::clickCalibBtn() {
    qDebug("打开相机标定窗口");
    this->setEnabled(false);
    auto cb = new calib(this);
    cb->show();
    cb->exec();
    delete cb;
    this->setEnabled(true);
}

void admin_system::clickPCLBtn() {
    qDebug("打开pcl相关窗口");
    this->setEnabled(false);
    auto pv = new pcl_visual(this);
    pv->show();
    pv->exec();
    delete pv;
    this->setEnabled(true);
}
