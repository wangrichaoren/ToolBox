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
    QVTKWidget *qvtkWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *pcl_visual)
    {
        if (pcl_visual->objectName().isEmpty())
            pcl_visual->setObjectName(QString::fromUtf8("pcl_visual"));
        pcl_visual->resize(887, 776);
        gridLayout = new QGridLayout(pcl_visual);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        qvtkWidget = new QVTKWidget(pcl_visual);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));

        gridLayout->addWidget(qvtkWidget, 0, 0, 1, 1);

        pushButton = new QPushButton(pcl_visual);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);


        retranslateUi(pcl_visual);

        QMetaObject::connectSlotsByName(pcl_visual);
    } // setupUi

    void retranslateUi(QDialog *pcl_visual)
    {
        pcl_visual->setWindowTitle(QCoreApplication::translate("pcl_visual", "pcl_visual", nullptr));
        pushButton->setText(QCoreApplication::translate("pcl_visual", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pcl_visual: public Ui_pcl_visual {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCL_VISUAL_H
