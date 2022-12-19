//
// Created by wrc on 22-12-6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_encoder.h" resolved


#include "utils.h"
#include "encoder.h"
#include "ui_encoder.h"

using namespace std;

encoder::encoder(QWidget *parent) :
        QDialog(parent), ui(new Ui::encoder) {
    ui->setupUi(this);

    connect(ui->pushButton1, &QPushButton::clicked, this, &encoder::clickBtn1);
    connect(ui->pushButton2, &QPushButton::clicked, this, &encoder::clickBtn2);
    connect(ui->pushButton3, &QPushButton::clicked, this, &encoder::clickBtn3);
    connect(ui->pushButton4, &QPushButton::clicked, this, &encoder::clickBtn4);
    connect(ui->pushButton5, &QPushButton::clicked, this, &encoder::clickBtn5);
}

encoder::~encoder() {
    // static自动回收
//    delete MasterEncoder::getInstance();
    std::cout << "xxx encoder" << std::endl;
    delete ui;
}

void encoder::clickBtn1() {
    string file_path = QFileDialog::getOpenFileName(this, "选择要加密的文件", "/home/wrc/Documents",
                                                    ";;").toStdString();
    if (file_path.empty()) {
        cout << "no choose" << endl;
        return;
    }
    cout << "encoder file path: " << file_path << endl;
    auto ienc = file_path.find(".enc");
    auto ikey = file_path.find(".key");

    if (ikey != string::npos) {
        showMessageBox(this, "危险操作!当前选取的文件为秘钥文件!");
        return;
    }

    if (ienc != string::npos) {
        showMessageBox(this, "危险操作!当前选取的文件可能已经加密!");
        return;
    }
    this->choose_encode_path = file_path;
    file_size = (double) (getFileSize(file_path.data()));
    ui->lcdNumber->display(int(getFileSize(file_path.data())));
    ui->progressBar->setValue(0);
}

void encoder::clickBtn2() {
    if (choose_encode_path.empty()) {
        cout << "no choose encode path" << endl;
        return;
    }
    setBtnenable(false);
    mec.clearProgress();
    auto k = QtConcurrent::run([this] { return UpdateProgress(); });
    // 加密，生成加密文件和key
    mec.encrypt(choose_encode_path);
    cout << "encoder file successful!" << endl;
    k.waitForFinished();
    choose_encode_path.clear();
    ui->lcdNumber->display(0);
    setBtnenable(true);
}

void encoder::clickBtn3() {
    string file_path = QFileDialog::getOpenFileName(this, "选择要解密的文件", "/home/wrc/Documents",
                                                    "(*.enc);;").toStdString();
    if (file_path.empty()) {
        cout << "no choose" << endl;
        return;
    }
    file_size = (double) (getFileSize(file_path.data()));
    this->choose_decode_path = file_path;
    ui->lcdNumber->display(int(getFileSize(file_path.data())));
}

void encoder::clickBtn4() {
    if (choose_decode_path.empty() || choose_key_path.empty()) {
        cout << "no choose path" << endl;
        return;
    }
    setBtnenable(false);
    mec.clearProgress();
    auto k = QtConcurrent::run([this] { return UpdateProgress(); });
    mec.decrypt(choose_decode_path, choose_key_path);

    cout << "decoder file successful!" << endl;
    k.waitForFinished();

    choose_decode_path.clear();
    choose_key_path.clear();
    ui->lcdNumber->display(0);
    setBtnenable(true);
}

void encoder::UpdateProgress() {
    while (true) {
        auto i = mec.getProgress();
        int n = (int) ((i / file_size) * 100);
        ui->progressBar->setValue(n);
        if (i == file_size) {
            return;
        }
    }
}


void encoder::clickBtn5() {
    string file_path = QFileDialog::getOpenFileName(this, "选择秘钥文件", "/home/wrc/Documents",
                                                    "(*.key);;").toStdString();
    if (file_path.empty()) {
        cout << "no choose" << endl;
        return;
    }

    this->choose_key_path = file_path;
}

void encoder::setBtnenable(bool flag) {
    ui->pushButton1->setEnabled(flag);
    ui->pushButton2->setEnabled(flag);
    ui->pushButton3->setEnabled(flag);
    ui->pushButton4->setEnabled(flag);
    ui->pushButton5->setEnabled(flag);
}


