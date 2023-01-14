//
// Created by wrc on 22-12-5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_window.h" resolved

#include <iostream>
#include <string>
#include <QDialog>
#include "main_window.h"
#include "ui_main_window.h"
#include "encoder.h"
#include "utils.h"
#include "admin_system.h"

using namespace std;

main_window::main_window(QWidget *parent) :
        QWidget(parent), ui(new Ui::main_window) {
    ui->setupUi(this);

    this->setMouseTracking(true);
    this->move(1920 / 2 - this->width() / 2, 1080 / 2 - this->height() / 2);
    this->setWindowIcon(QIcon(":/icons/icon.png"));


    setIconToLabel(ui->label7, ":/icons/icon4.png");
    setIconToLabel(ui->label8, ":/icons/icon2.png");
    setIconToLabel(ui->label9, ":/icons/icon3.png");
    setIconToLabel(ui->label10, ":/icons/icon1.png");

    setIconToLabel(ui->label1, ":/icons/encoder.png");

    setIconToLabel(ui->label1_2, ":/icons/exit.png");

    ui->lineEdit->setText("admin");

    connect(ui->pushButton, &QPushButton::clicked, this, &main_window::clickBtn0);
    connect(ui->pushButton1, &QPushButton::clicked, this, &main_window::clickBtn1);
    connect(ui->pushButton2, &QPushButton::clicked, this, &main_window::clickBtn2);
}

main_window::~main_window() {
    cout << "xxx main_window" << endl;
    delete ui;
}

/**
 * 加解密文件
 */
void main_window::clickBtn0() {
    auto e = new encoder(this);
    e->show();
    e->exec();
    delete e;
}

void main_window::clickBtn1() {
    std::cout << "单击了关闭按钮!" << std::endl;
    close();
}

void main_window::clickBtn2() {
    // todo 简易的密钥 admin
    if (ui->lineEdit->text().toStdString() == "admin") {
        auto as = new admin_system(this);
        as->show();
        as->exec();
        delete as;
    } else {
        showMessageBox(this, "输入的管理员密码错误,请核对/申请密钥!");
        return;
    }
}
