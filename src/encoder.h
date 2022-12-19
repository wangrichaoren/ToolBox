//
// Created by wrc on 22-12-6.
//

#ifndef TOOLBOX_ENCODER_H
#define TOOLBOX_ENCODER_H

#include <QDialog>
#include <QObject>
#include <QThread>
#include <string>
#include <QtConcurrent/QtConcurrent>
#include <iostream>
#include <QFileDialog>
#include <myencoder.h>

QT_BEGIN_NAMESPACE
namespace Ui { class encoder; }
QT_END_NAMESPACE


class WorkThread:public QObject{

};

class encoder : public QDialog {
Q_OBJECT

public:
    explicit encoder(QWidget *parent = nullptr);

    ~encoder() override;

    void UpdateProgress();

    void clickBtn1();

    void clickBtn2();

    void clickBtn3();

    void clickBtn4();

    void clickBtn5();

    void setBtnenable(bool flag);

private:
    std::string choose_encode_path{};
    std::string choose_decode_path{};
    std::string choose_key_path{};

    Ui::encoder *ui;
    double file_size{0.0};
    bool is_start{false};
    myencoder mec;
};


#endif //TOOLBOX_ENCODER_H
