/********************************************************************************
** Form generated from reading UI file 'start_window.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_WINDOW_H
#define UI_START_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_start_window
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *file_encryption_btn;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pc_visual_btn;
    QSpacerItem *verticalSpacer_3;
    QPushButton *exit_btn;
    QPushButton *match_btn;
    QPushButton *cam_calib_btn;
    QPushButton *face_det_btn;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *start_window)
    {
        if (start_window->objectName().isEmpty())
            start_window->setObjectName(QString::fromUtf8("start_window"));
        start_window->resize(777, 550);
        gridLayout_2 = new QGridLayout(start_window);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(start_window);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(55);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));\n"
"\n"
""));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        groupBox = new QGroupBox(start_window);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(150, 100));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(false);
        font1.setWeight(50);
        groupBox->setFont(font1);
        groupBox->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        file_encryption_btn = new QPushButton(groupBox);
        file_encryption_btn->setObjectName(QString::fromUtf8("file_encryption_btn"));
        sizePolicy1.setHeightForWidth(file_encryption_btn->sizePolicy().hasHeightForWidth());
        file_encryption_btn->setSizePolicy(sizePolicy1);
        file_encryption_btn->setMinimumSize(QSize(0, 0));
        QFont font2;
        font2.setPointSize(15);
        font2.setBold(true);
        font2.setWeight(75);
        file_encryption_btn->setFont(font2);
        file_encryption_btn->setStyleSheet(QString::fromUtf8(" QPushButton:hover { \n"
"	color: rgb(255, 255, 255);\n"
"    background-color: rgb(100, 150, 170); \n"
"}\n"
""));

        gridLayout->addWidget(file_encryption_btn, 0, 0, 1, 1);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setFont(font2);
        pushButton->setStyleSheet(QString::fromUtf8(" QPushButton:hover { \n"
"	color: rgb(255, 255, 255);\n"
"    background-color: rgb(100, 150, 170); \n"
"}\n"
""));

        gridLayout->addWidget(pushButton, 4, 4, 1, 1);

        verticalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(verticalSpacer_2, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        pc_visual_btn = new QPushButton(groupBox);
        pc_visual_btn->setObjectName(QString::fromUtf8("pc_visual_btn"));
        sizePolicy1.setHeightForWidth(pc_visual_btn->sizePolicy().hasHeightForWidth());
        pc_visual_btn->setSizePolicy(sizePolicy1);
        pc_visual_btn->setFont(font2);
        pc_visual_btn->setStyleSheet(QString::fromUtf8(" QPushButton:hover { \n"
"	color: rgb(255, 255, 255);\n"
"    background-color: rgb(100, 150, 170); \n"
"}\n"
""));

        gridLayout->addWidget(pc_visual_btn, 4, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 0, 1, 1, 1);

        exit_btn = new QPushButton(groupBox);
        exit_btn->setObjectName(QString::fromUtf8("exit_btn"));
        sizePolicy1.setHeightForWidth(exit_btn->sizePolicy().hasHeightForWidth());
        exit_btn->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(true);
        font3.setWeight(75);
        exit_btn->setFont(font3);
        exit_btn->setStyleSheet(QString::fromUtf8(" QPushButton:hover { \n"
"	color: rgb(255, 255, 255);\n"
"    background-color: rgb(100, 150, 170); \n"
"}\n"
""));

        gridLayout->addWidget(exit_btn, 6, 0, 1, 5);

        match_btn = new QPushButton(groupBox);
        match_btn->setObjectName(QString::fromUtf8("match_btn"));
        sizePolicy1.setHeightForWidth(match_btn->sizePolicy().hasHeightForWidth());
        match_btn->setSizePolicy(sizePolicy1);
        match_btn->setMinimumSize(QSize(0, 0));
        match_btn->setFont(font2);
        match_btn->setStyleSheet(QString::fromUtf8(" QPushButton:hover { \n"
"	color: rgb(255, 255, 255);\n"
"    background-color: rgb(100, 150, 170); \n"
"}\n"
""));

        gridLayout->addWidget(match_btn, 0, 2, 1, 1);

        cam_calib_btn = new QPushButton(groupBox);
        cam_calib_btn->setObjectName(QString::fromUtf8("cam_calib_btn"));
        sizePolicy1.setHeightForWidth(cam_calib_btn->sizePolicy().hasHeightForWidth());
        cam_calib_btn->setSizePolicy(sizePolicy1);
        cam_calib_btn->setFont(font2);
        cam_calib_btn->setStyleSheet(QString::fromUtf8(" QPushButton:hover { \n"
"	color: rgb(255, 255, 255);\n"
"    background-color: rgb(100, 150, 170); \n"
"}\n"
""));

        gridLayout->addWidget(cam_calib_btn, 0, 4, 1, 1);

        face_det_btn = new QPushButton(groupBox);
        face_det_btn->setObjectName(QString::fromUtf8("face_det_btn"));
        sizePolicy1.setHeightForWidth(face_det_btn->sizePolicy().hasHeightForWidth());
        face_det_btn->setSizePolicy(sizePolicy1);
        face_det_btn->setFont(font2);
        face_det_btn->setStyleSheet(QString::fromUtf8(" QPushButton:hover { \n"
"	color: rgb(255, 255, 255);\n"
"    background-color: rgb(100, 150, 170); \n"
"}\n"
""));

        gridLayout->addWidget(face_det_btn, 4, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 0, 3, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);


        retranslateUi(start_window);

        QMetaObject::connectSlotsByName(start_window);
    } // setupUi

    void retranslateUi(QWidget *start_window)
    {
        start_window->setWindowTitle(QCoreApplication::translate("start_window", "TOOL BOX", nullptr));
        label->setText(QCoreApplication::translate("start_window", "TOOL  BOX", nullptr));
        groupBox->setTitle(QString());
#if QT_CONFIG(statustip)
        file_encryption_btn->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        file_encryption_btn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        file_encryption_btn->setText(QCoreApplication::translate("start_window", "\346\226\207\344\273\266\345\212\240\345\257\206\345\212\251\346\211\213", nullptr));
        pushButton->setText(QCoreApplication::translate("start_window", "TODO ...", nullptr));
        pc_visual_btn->setText(QCoreApplication::translate("start_window", "\347\202\271\344\272\221\346\237\245\347\234\213\345\231\250", nullptr));
        exit_btn->setText(QCoreApplication::translate("start_window", "\351\200\200\345\207\272", nullptr));
        match_btn->setText(QCoreApplication::translate("start_window", "\346\250\241\346\235\277\345\214\271\351\205\215", nullptr));
        cam_calib_btn->setText(QCoreApplication::translate("start_window", "\347\233\270\346\234\272\346\240\207\345\256\232", nullptr));
        face_det_btn->setText(QCoreApplication::translate("start_window", "\344\272\272\350\204\270\350\257\206\345\210\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class start_window: public Ui_start_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_WINDOW_H
