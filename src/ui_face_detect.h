/********************************************************************************
** Form generated from reading UI file 'face_detect.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACE_DETECT_H
#define UI_FACE_DETECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_face_detect
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *pushButtonOpenCam;
    QGroupBox *groupBox_2;
    QPushButton *pushButtonDet;
    QPushButton *pushButtonCloseCam;

    void setupUi(QDialog *face_detect)
    {
        if (face_detect->objectName().isEmpty())
            face_detect->setObjectName(QStringLiteral("face_detect"));
        face_detect->resize(994, 887);
        gridLayout = new QGridLayout(face_detect);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new QGraphicsView(face_detect);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(976, 612));
        graphicsView->setMaximumSize(QSize(976, 612));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 3);

        groupBox = new QGroupBox(face_detect);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        gridLayout_2->addWidget(radioButton, 0, 0, 1, 1);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        gridLayout_2->addWidget(radioButton_2, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox, 1, 0, 3, 1);

        pushButtonOpenCam = new QPushButton(face_detect);
        pushButtonOpenCam->setObjectName(QStringLiteral("pushButtonOpenCam"));

        gridLayout->addWidget(pushButtonOpenCam, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(face_detect);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));

        gridLayout->addWidget(groupBox_2, 1, 2, 3, 1);

        pushButtonDet = new QPushButton(face_detect);
        pushButtonDet->setObjectName(QStringLiteral("pushButtonDet"));

        gridLayout->addWidget(pushButtonDet, 2, 1, 1, 1);

        pushButtonCloseCam = new QPushButton(face_detect);
        pushButtonCloseCam->setObjectName(QStringLiteral("pushButtonCloseCam"));

        gridLayout->addWidget(pushButtonCloseCam, 3, 1, 1, 1);


        retranslateUi(face_detect);

        QMetaObject::connectSlotsByName(face_detect);
    } // setupUi

    void retranslateUi(QDialog *face_detect)
    {
        face_detect->setWindowTitle(QApplication::translate("face_detect", "\344\272\272\350\204\270\350\257\206\345\210\253", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("face_detect", "\351\200\211\351\241\271", Q_NULLPTR));
        radioButton->setText(QApplication::translate("face_detect", "\346\234\254\345\234\260\347\233\270\346\234\272", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("face_detect", "\345\244\226\351\203\250&USB\347\233\270\346\234\272", Q_NULLPTR));
        pushButtonOpenCam->setText(QApplication::translate("face_detect", "\346\211\223\345\274\200\347\233\270\346\234\272", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("face_detect", "\344\277\241\346\201\257", Q_NULLPTR));
        pushButtonDet->setText(QApplication::translate("face_detect", "\345\274\200\345\220\257\344\272\272\350\204\270\346\243\200\346\265\213", Q_NULLPTR));
        pushButtonCloseCam->setText(QApplication::translate("face_detect", "\345\205\263\351\227\255\347\233\270\346\234\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class face_detect: public Ui_face_detect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACE_DETECT_H
