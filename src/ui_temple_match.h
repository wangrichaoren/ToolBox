/********************************************************************************
** Form generated from reading UI file 'temple_match.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPLE_MATCH_H
#define UI_TEMPLE_MATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_temple_match
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonChoose;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButtonTrain;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QToolBox *toolBox;
    QWidget *page;
    QGridLayout *gridLayout_5;
    QLabel *label_4;
    QLineEdit *lineEditWeak;
    QLabel *label_5;
    QLineEdit *lineEditStrong;
    QLabel *label_10;
    QLineEdit *lineEditDepth;
    QLabel *label_11;
    QLineEdit *lineEditNMS;
    QWidget *page_2;
    QGridLayout *gridLayout_6;
    QLabel *label_9;
    QLineEdit *lineEditFutrueNum;
    QLabel *label_2;
    QLineEdit *lineEditRotationRange;
    QLabel *label_3;
    QLineEdit *lineEditRotationStep;
    QLabel *label_8;
    QLineEdit *lineEditScaleRange;
    QLabel *label_7;
    QLineEdit *lineEditScaleStep;
    QLineEdit *lineEdithreshold;
    QLabel *label_6;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QGraphicsView *graphicsViewTemplate;
    QComboBox *comboBox;
    QPushButton *pushButtonDet;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QDialog *temple_match)
    {
        if (temple_match->objectName().isEmpty())
            temple_match->setObjectName(QStringLiteral("temple_match"));
        temple_match->resize(963, 972);
        gridLayout = new QGridLayout(temple_match);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new QGraphicsView(temple_match);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMinimumSize(QSize(878, 551));
        graphicsView->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        scrollArea = new QScrollArea(temple_match);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setMinimumSize(QSize(751, 221));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 943, 395));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 1, 1, 1);

        pushButtonChoose = new QPushButton(scrollAreaWidgetContents);
        pushButtonChoose->setObjectName(QStringLiteral("pushButtonChoose"));
        pushButtonChoose->setMinimumSize(QSize(161, 51));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        pushButtonChoose->setFont(font);

        gridLayout_2->addWidget(pushButtonChoose, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 4, 1, 1, 1);

        pushButtonTrain = new QPushButton(scrollAreaWidgetContents);
        pushButtonTrain->setObjectName(QStringLiteral("pushButtonTrain"));
        pushButtonTrain->setMinimumSize(QSize(161, 51));
        pushButtonTrain->setFont(font);

        gridLayout_2->addWidget(pushButtonTrain, 3, 1, 1, 1);

        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(320, 350));
        groupBox->setMaximumSize(QSize(320, 350));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        groupBox->setFont(font1);
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        toolBox = new QToolBox(groupBox);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 272, 191));
        gridLayout_5 = new QGridLayout(page);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_4 = new QLabel(page);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);

        lineEditWeak = new QLineEdit(page);
        lineEditWeak->setObjectName(QStringLiteral("lineEditWeak"));

        gridLayout_5->addWidget(lineEditWeak, 0, 1, 1, 1);

        label_5 = new QLabel(page);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_5, 1, 0, 1, 1);

        lineEditStrong = new QLineEdit(page);
        lineEditStrong->setObjectName(QStringLiteral("lineEditStrong"));

        gridLayout_5->addWidget(lineEditStrong, 1, 1, 1, 1);

        label_10 = new QLabel(page);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font2);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_10, 2, 0, 1, 1);

        lineEditDepth = new QLineEdit(page);
        lineEditDepth->setObjectName(QStringLiteral("lineEditDepth"));

        gridLayout_5->addWidget(lineEditDepth, 2, 1, 1, 1);

        label_11 = new QLabel(page);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setFont(font2);
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_11, 3, 0, 1, 1);

        lineEditNMS = new QLineEdit(page);
        lineEditNMS->setObjectName(QStringLiteral("lineEditNMS"));

        gridLayout_5->addWidget(lineEditNMS, 3, 1, 1, 1);

        toolBox->addItem(page, QString::fromUtf8("\351\253\230\347\272\247"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 272, 191));
        gridLayout_6 = new QGridLayout(page_2);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        label_9 = new QLabel(page_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font2);
        label_9->setLayoutDirection(Qt::LeftToRight);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_9, 0, 0, 1, 1);

        lineEditFutrueNum = new QLineEdit(page_2);
        lineEditFutrueNum->setObjectName(QStringLiteral("lineEditFutrueNum"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditFutrueNum->sizePolicy().hasHeightForWidth());
        lineEditFutrueNum->setSizePolicy(sizePolicy);
        lineEditFutrueNum->setMinimumSize(QSize(167, 25));
        lineEditFutrueNum->setMaximumSize(QSize(167, 25));

        gridLayout_6->addWidget(lineEditFutrueNum, 0, 1, 1, 1);

        label_2 = new QLabel(page_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font2);
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setTextFormat(Qt::AutoText);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_2, 1, 0, 1, 1);

        lineEditRotationRange = new QLineEdit(page_2);
        lineEditRotationRange->setObjectName(QStringLiteral("lineEditRotationRange"));
        sizePolicy.setHeightForWidth(lineEditRotationRange->sizePolicy().hasHeightForWidth());
        lineEditRotationRange->setSizePolicy(sizePolicy);
        lineEditRotationRange->setMinimumSize(QSize(167, 25));
        lineEditRotationRange->setMaximumSize(QSize(167, 25));

        gridLayout_6->addWidget(lineEditRotationRange, 1, 1, 1, 1);

        label_3 = new QLabel(page_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font2);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_3, 2, 0, 1, 1);

        lineEditRotationStep = new QLineEdit(page_2);
        lineEditRotationStep->setObjectName(QStringLiteral("lineEditRotationStep"));
        lineEditRotationStep->setMinimumSize(QSize(167, 25));
        lineEditRotationStep->setMaximumSize(QSize(167, 25));

        gridLayout_6->addWidget(lineEditRotationStep, 2, 1, 1, 1);

        label_8 = new QLabel(page_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font2);
        label_8->setLayoutDirection(Qt::LeftToRight);
        label_8->setTextFormat(Qt::AutoText);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_8, 3, 0, 1, 1);

        lineEditScaleRange = new QLineEdit(page_2);
        lineEditScaleRange->setObjectName(QStringLiteral("lineEditScaleRange"));
        lineEditScaleRange->setMinimumSize(QSize(167, 25));
        lineEditScaleRange->setMaximumSize(QSize(167, 25));

        gridLayout_6->addWidget(lineEditScaleRange, 3, 1, 1, 1);

        label_7 = new QLabel(page_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font2);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_7, 4, 0, 1, 1);

        lineEditScaleStep = new QLineEdit(page_2);
        lineEditScaleStep->setObjectName(QStringLiteral("lineEditScaleStep"));
        lineEditScaleStep->setMaximumSize(QSize(167, 25));

        gridLayout_6->addWidget(lineEditScaleStep, 4, 1, 1, 1);

        toolBox->addItem(page_2, QString::fromUtf8("\351\200\232\347\224\250"));

        gridLayout_3->addWidget(toolBox, 0, 0, 1, 2);

        lineEdithreshold = new QLineEdit(groupBox);
        lineEdithreshold->setObjectName(QStringLiteral("lineEdithreshold"));
        lineEdithreshold->setMinimumSize(QSize(180, 35));
        lineEdithreshold->setMaximumSize(QSize(180, 16777215));
        QFont font3;
        font3.setPointSize(14);
        lineEdithreshold->setFont(font3);

        gridLayout_3->addWidget(lineEdithreshold, 1, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(75, 35));
        label_6->setMaximumSize(QSize(75, 35));
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(false);
        font4.setWeight(50);
        label_6->setFont(font4);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 7, 1);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(320, 350));
        groupBox_2->setMaximumSize(QSize(320, 350));
        groupBox_2->setFont(font1);
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        graphicsViewTemplate = new QGraphicsView(groupBox_2);
        graphicsViewTemplate->setObjectName(QStringLiteral("graphicsViewTemplate"));
        sizePolicy.setHeightForWidth(graphicsViewTemplate->sizePolicy().hasHeightForWidth());
        graphicsViewTemplate->setSizePolicy(sizePolicy);
        graphicsViewTemplate->setMinimumSize(QSize(250, 170));
        graphicsViewTemplate->setMaximumSize(QSize(250, 170));
        graphicsViewTemplate->setStyleSheet(QStringLiteral(""));

        gridLayout_4->addWidget(graphicsViewTemplate, 2, 0, 1, 1);

        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(250, 31));
        comboBox->setMaximumSize(QSize(250, 31));

        gridLayout_4->addWidget(comboBox, 1, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 0, 2, 7, 1);

        pushButtonDet = new QPushButton(scrollAreaWidgetContents);
        pushButtonDet->setObjectName(QStringLiteral("pushButtonDet"));
        pushButtonDet->setMinimumSize(QSize(161, 51));
        pushButtonDet->setFont(font);

        gridLayout_2->addWidget(pushButtonDet, 5, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 0, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 6, 1, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 1, 0, 1, 1);


        retranslateUi(temple_match);

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(temple_match);
    } // setupUi

    void retranslateUi(QDialog *temple_match)
    {
        temple_match->setWindowTitle(QApplication::translate("temple_match", "\346\250\241\346\235\277\345\214\271\351\205\215", Q_NULLPTR));
        pushButtonChoose->setText(QApplication::translate("temple_match", "\351\200\211\346\213\251\346\226\207\344\273\266", Q_NULLPTR));
        pushButtonTrain->setText(QApplication::translate("temple_match", "\350\256\255\347\273\203\346\250\241\346\235\277", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("temple_match", "\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        label_4->setText(QApplication::translate("temple_match", "\345\274\261\351\230\210\345\200\274", Q_NULLPTR));
        lineEditWeak->setText(QApplication::translate("temple_match", "30", Q_NULLPTR));
        lineEditWeak->setPlaceholderText(QApplication::translate("temple_match", "\351\273\230\350\256\244\345\274\261\351\230\210\345\200\27430", Q_NULLPTR));
        label_5->setText(QApplication::translate("temple_match", "\345\274\272\351\230\210\345\200\274", Q_NULLPTR));
        lineEditStrong->setText(QApplication::translate("temple_match", "60", Q_NULLPTR));
        lineEditStrong->setPlaceholderText(QApplication::translate("temple_match", "\351\273\230\350\256\244\345\274\272\351\230\210\345\200\27460", Q_NULLPTR));
        label_10->setText(QApplication::translate("temple_match", "\351\207\207\346\240\267\346\267\261\345\272\246", Q_NULLPTR));
        lineEditDepth->setText(QApplication::translate("temple_match", "4,8", Q_NULLPTR));
        lineEditDepth->setPlaceholderText(QApplication::translate("temple_match", "\351\273\230\350\256\244\351\207\207\346\240\267\346\267\261\345\272\2464-8", Q_NULLPTR));
        label_11->setText(QApplication::translate("temple_match", "nms\351\230\210\345\200\274", Q_NULLPTR));
        lineEditNMS->setText(QApplication::translate("temple_match", "0.1", Q_NULLPTR));
        lineEditNMS->setPlaceholderText(QApplication::translate("temple_match", "\351\273\230\350\256\244nms\351\230\210\345\200\2740.1", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("temple_match", "\351\253\230\347\272\247", Q_NULLPTR));
        label_9->setText(QApplication::translate("temple_match", "\347\211\271\345\276\201\346\225\260\351\207\217", Q_NULLPTR));
        lineEditFutrueNum->setText(QApplication::translate("temple_match", "300", Q_NULLPTR));
        lineEditFutrueNum->setPlaceholderText(QApplication::translate("temple_match", "\347\211\271\345\276\201\347\202\271\346\225\260\351\207\217", Q_NULLPTR));
        label_2->setText(QApplication::translate("temple_match", "\346\227\213\350\275\254\350\214\203\345\233\264", Q_NULLPTR));
        lineEditRotationRange->setText(QApplication::translate("temple_match", "0,360", Q_NULLPTR));
        lineEditRotationRange->setPlaceholderText(QApplication::translate("temple_match", "\346\227\213\350\275\254\350\214\203\345\233\264,\345\210\206\351\232\224\347\254\246\",/\357\274\214\"", Q_NULLPTR));
        label_3->setText(QApplication::translate("temple_match", "\346\227\213\350\275\254\346\255\245\351\225\277", Q_NULLPTR));
        lineEditRotationStep->setText(QApplication::translate("temple_match", "1", Q_NULLPTR));
        lineEditRotationStep->setPlaceholderText(QApplication::translate("temple_match", "\346\255\245\351\225\277,\345\210\206\351\232\224\347\254\246\",/\357\274\214\"", Q_NULLPTR));
        label_8->setText(QApplication::translate("temple_match", "\347\274\251\346\224\276\350\214\203\345\233\264", Q_NULLPTR));
        lineEditScaleRange->setText(QApplication::translate("temple_match", "0.9,1", Q_NULLPTR));
        lineEditScaleRange->setPlaceholderText(QApplication::translate("temple_match", "\346\227\213\350\275\254\350\214\203\345\233\264,\345\210\206\351\232\224\347\254\246\",/\357\274\214\"", Q_NULLPTR));
        label_7->setText(QApplication::translate("temple_match", "\347\274\251\346\224\276\346\255\245\351\225\277", Q_NULLPTR));
        lineEditScaleStep->setText(QApplication::translate("temple_match", "0.1", Q_NULLPTR));
        lineEditScaleStep->setPlaceholderText(QApplication::translate("temple_match", "\346\255\245\351\225\277,\345\210\206\351\232\224\347\254\246\",/\357\274\214\"", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("temple_match", "\351\200\232\347\224\250", Q_NULLPTR));
        lineEdithreshold->setText(QApplication::translate("temple_match", "90", Q_NULLPTR));
        lineEdithreshold->setPlaceholderText(QApplication::translate("temple_match", "X>=\344\270\272\350\277\207\346\273\244\347\225\214\351\231\220", Q_NULLPTR));
        label_6->setText(QApplication::translate("temple_match", "\345\210\206\346\225\260\351\230\210\345\200\274", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("temple_match", "\345\216\206\345\217\262\346\263\250\345\206\214\346\250\241\346\235\277", Q_NULLPTR));
        pushButtonDet->setText(QApplication::translate("temple_match", "\346\250\241\346\235\277\345\214\271\351\205\215", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class temple_match: public Ui_temple_match {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLE_MATCH_H
