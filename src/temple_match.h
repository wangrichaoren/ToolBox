//
// Created by wrc on 22-12-8.
//

#ifndef TOOLBOX_TEMPLE_MATCH_H
#define TOOLBOX_TEMPLE_MATCH_H

#include <QDialog>
#include <QFileDialog>
#include <string>
#include <iostream>
#include "imagewidget.h"
#include "utils.h"
#include <dirent.h>
#include "line2Dup.h"
#include "3rdParty/include/yaml-cpp/yaml.h"
#include <yaml-cpp/node/parse.h>


using namespace std;
//namespace fs = std::experimental::filesystem;

const string path = get_abs_path("../datas/templates/");
const string cfg_path = get_abs_path("../config/cfg.yaml");
//const string cfg_path{"../config/cfg.yaml"};


QT_BEGIN_NAMESPACE
namespace Ui { class temple_match; }
QT_END_NAMESPACE

class temple_match : public QDialog {
Q_OBJECT

public:
    explicit temple_match(QWidget *parent = nullptr);

    void clickChooseBtn();

    void clickTrainBtn();

    void clickDetBtn();

    void changeComBoxChoose();

    void initUpdateInfo();

    ~temple_match() override;

private:
//    LineModDetector *detector{nullptr};
    ImageWidget *m_Image{nullptr};
    ImageWidget *m_Image_temp{nullptr};
    Ui::temple_match *ui;
    string chooseFilePath{};
    bool isTrainOk{false};
    YAML::Node config;
//    TRAIN_RESULT trainResult;

private slots:

    bool eventFilter(QObject *watched, QEvent *event);
};


#endif //TOOLBOX_TEMPLE_MATCH_H
