/********************************************************************************
** Form generated from reading UI file 'pcl_visual.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCL_VISUAL_H
#define UI_PCL_VISUAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_pcl_visual
{
public:
    QGridLayout *gridLayout;
    QPushButton *savePushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QVTKWidget *qvtkWidget;
    QPushButton *openPushButton;
    QPushButton *showCoordPushButton;

    void setupUi(QDialog *pcl_visual)
    {
        if (pcl_visual->objectName().isEmpty())
            pcl_visual->setObjectName(QString::fromUtf8("pcl_visual"));
        pcl_visual->resize(868, 846);
        gridLayout = new QGridLayout(pcl_visual);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        savePushButton = new QPushButton(pcl_visual);
        savePushButton->setObjectName(QString::fromUtf8("savePushButton"));

        gridLayout->addWidget(savePushButton, 4, 1, 1, 1);

        pushButton_2 = new QPushButton(pcl_visual);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 5, 1, 1, 1);

        pushButton = new QPushButton(pcl_visual);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMaximumSize(QSize(160, 16777215));
        pushButton->setSizeIncrement(QSize(160, 0));
        pushButton->setBaseSize(QSize(160, 0));

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        qvtkWidget = new QVTKWidget(pcl_visual);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));

        gridLayout->addWidget(qvtkWidget, 0, 0, 1, 3);

        openPushButton = new QPushButton(pcl_visual);
        openPushButton->setObjectName(QString::fromUtf8("openPushButton"));

        gridLayout->addWidget(openPushButton, 3, 1, 1, 1);

        showCoordPushButton = new QPushButton(pcl_visual);
        showCoordPushButton->setObjectName(QString::fromUtf8("showCoordPushButton"));

        gridLayout->addWidget(showCoordPushButton, 2, 1, 1, 1);


        retranslateUi(pcl_visual);

        QMetaObject::connectSlotsByName(pcl_visual);
    } // setupUi

    void retranslateUi(QDialog *pcl_visual)
    {
        pcl_visual->setWindowTitle(QCoreApplication::translate("pcl_visual", "\347\202\271\344\272\221\346\237\245\347\234\213\345\231\250", nullptr));
        savePushButton->setText(QCoreApplication::translate("pcl_visual", "\344\277\235\345\255\230\347\202\271\344\272\221", nullptr));
        pushButton_2->setText(QCoreApplication::translate("pcl_visual", "\346\240\274\345\274\217\350\275\254\346\215\242", nullptr));
        pushButton->setText(QCoreApplication::translate("pcl_visual", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        openPushButton->setText(QCoreApplication::translate("pcl_visual", "\345\220\257\345\212\250\347\233\270\346\234\272", nullptr));
        showCoordPushButton->setText(QCoreApplication::translate("pcl_visual", "\346\230\276\347\244\272\345\235\220\346\240\207\350\275\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pcl_visual: public Ui_pcl_visual {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCL_VISUAL_H
