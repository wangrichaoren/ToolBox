/********************************************************************************
** Form generated from reading UI file 'encoder.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENCODER_H
#define UI_ENCODER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLayout>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_encoder
{
public:
    QToolBox *toolBox;
    QWidget *page;
    QGroupBox *groupBox;
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QWidget *page_2;
    QGroupBox *groupBox_2;
    QPushButton *pushButton3;
    QPushButton *pushButton4;
    QPushButton *pushButton5;
    QLCDNumber *lcdNumber;
    QProgressBar *progressBar;

    void setupUi(QDialog *encoder)
    {
        if (encoder->objectName().isEmpty())
            encoder->setObjectName(QStringLiteral("encoder"));
        encoder->resize(465, 469);
        toolBox = new QToolBox(encoder);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setEnabled(true);
        toolBox->setGeometry(QRect(100, 90, 271, 331));
        QFont font;
        font.setPointSize(17);
        font.setBold(true);
        font.setWeight(75);
        toolBox->setFont(font);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 271, 235));
        groupBox = new QGroupBox(page);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 0, 221, 181));
        pushButton1 = new QPushButton(groupBox);
        pushButton1->setObjectName(QStringLiteral("pushButton1"));
        pushButton1->setGeometry(QRect(50, 50, 121, 41));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(false);
        font1.setWeight(50);
        pushButton1->setFont(font1);
        pushButton2 = new QPushButton(groupBox);
        pushButton2->setObjectName(QStringLiteral("pushButton2"));
        pushButton2->setGeometry(QRect(50, 120, 121, 41));
        pushButton2->setFont(font1);
        toolBox->addItem(page, QString::fromUtf8("\346\226\207\344\273\266\345\212\240\345\257\206"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 271, 235));
        groupBox_2 = new QGroupBox(page_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, -30, 221, 251));
        pushButton3 = new QPushButton(groupBox_2);
        pushButton3->setObjectName(QStringLiteral("pushButton3"));
        pushButton3->setGeometry(QRect(50, 50, 121, 41));
        pushButton3->setFont(font1);
        pushButton4 = new QPushButton(groupBox_2);
        pushButton4->setObjectName(QStringLiteral("pushButton4"));
        pushButton4->setGeometry(QRect(50, 190, 121, 41));
        pushButton4->setFont(font1);
        pushButton5 = new QPushButton(groupBox_2);
        pushButton5->setObjectName(QStringLiteral("pushButton5"));
        pushButton5->setGeometry(QRect(50, 120, 121, 41));
        pushButton5->setFont(font1);
        toolBox->addItem(page_2, QString::fromUtf8("\346\226\207\344\273\266\350\247\243\345\257\206"));
        lcdNumber = new QLCDNumber(encoder);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(70, 20, 331, 61));
        QFont font2;
        font2.setPointSize(15);
        lcdNumber->setFont(font2);
        lcdNumber->setDigitCount(12);
        lcdNumber->setMode(QLCDNumber::Dec);
        progressBar = new QProgressBar(encoder);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 440, 441, 21));
        progressBar->setValue(0);

        retranslateUi(encoder);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(encoder);
    } // setupUi

    void retranslateUi(QDialog *encoder)
    {
        encoder->setWindowTitle(QApplication::translate("encoder", "\346\226\207\344\273\266\345\212\240\345\257\206\345\212\251\346\211\213", Q_NULLPTR));
        groupBox->setTitle(QString());
        pushButton1->setText(QApplication::translate("encoder", "\351\200\211\346\213\251\346\226\207\344\273\266", Q_NULLPTR));
        pushButton2->setText(QApplication::translate("encoder", "\346\211\247\350\241\214\345\212\240\345\257\206", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("encoder", "\346\226\207\344\273\266\345\212\240\345\257\206", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        pushButton3->setText(QApplication::translate("encoder", "\351\200\211\346\213\251\346\226\207\344\273\266", Q_NULLPTR));
        pushButton4->setText(QApplication::translate("encoder", "\346\211\247\350\241\214\350\247\243\345\257\206", Q_NULLPTR));
        pushButton5->setText(QApplication::translate("encoder", "\347\247\230\351\222\245\346\226\207\344\273\266", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("encoder", "\346\226\207\344\273\266\350\247\243\345\257\206", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class encoder: public Ui_encoder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENCODER_H
