/********************************************************************************
** Form generated from reading UI file 'calib.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIB_H
#define UI_CALIB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_calib
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QGraphicsView *graphicsView;
    QPushButton *pushButton_4;
    QProgressBar *progressBar;
    QPushButton *pushButton_1;

    void setupUi(QDialog *calib)
    {
        if (calib->objectName().isEmpty())
            calib->setObjectName(QStringLiteral("calib"));
        calib->resize(939, 822);
        gridLayout_2 = new QGridLayout(calib);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_2 = new QGroupBox(calib);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_3->addWidget(pushButton, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 2, 2, 4, 1);

        pushButton_2 = new QPushButton(calib);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 4, 1, 1, 1);

        pushButton_3 = new QPushButton(calib);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 5, 1, 1, 1);

        groupBox = new QGroupBox(calib);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        gridLayout->addWidget(radioButton, 0, 0, 1, 2);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        gridLayout->addWidget(radioButton_2, 0, 2, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 1, 1, 2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 3, 1, 1, 2);


        gridLayout_2->addWidget(groupBox, 2, 0, 4, 1);

        graphicsView = new QGraphicsView(calib);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout_2->addWidget(graphicsView, 0, 0, 1, 3);

        pushButton_4 = new QPushButton(calib);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 3, 1, 1, 1);

        progressBar = new QProgressBar(calib);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        gridLayout_2->addWidget(progressBar, 1, 0, 1, 3);

        pushButton_1 = new QPushButton(calib);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));

        gridLayout_2->addWidget(pushButton_1, 2, 1, 1, 1);


        retranslateUi(calib);

        QMetaObject::connectSlotsByName(calib);
    } // setupUi

    void retranslateUi(QDialog *calib)
    {
        calib->setWindowTitle(QApplication::translate("calib", "\347\233\270\346\234\272\346\240\207\345\256\232", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("calib", "\350\276\223\345\207\272\344\277\241\346\201\257", Q_NULLPTR));
        pushButton->setText(QApplication::translate("calib", "\351\252\214\350\257\201", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("calib", "\345\274\200\345\247\213\346\240\207\345\256\232", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("calib", "\351\200\200\345\207\272\346\240\207\345\256\232", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("calib", "\346\240\207\345\256\232\346\235\277\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        radioButton->setText(QApplication::translate("calib", "\346\243\213\347\233\230\346\240\274", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("calib", "\345\234\206\347\275\221\346\240\274", Q_NULLPTR));
        label->setText(QApplication::translate("calib", "\345\210\227", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("calib", "8", Q_NULLPTR));
        label_2->setText(QApplication::translate("calib", "\350\241\214", Q_NULLPTR));
        lineEdit_2->setText(QApplication::translate("calib", "5", Q_NULLPTR));
        label_3->setText(QApplication::translate("calib", "\351\227\264\350\267\235", Q_NULLPTR));
        lineEdit_3->setText(QApplication::translate("calib", "27", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("calib", "\346\215\225\350\216\267-space", Q_NULLPTR));
        pushButton_1->setText(QApplication::translate("calib", "\346\211\223\345\274\200\347\233\270\346\234\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class calib: public Ui_calib {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIB_H
