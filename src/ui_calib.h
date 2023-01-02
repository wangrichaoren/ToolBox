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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_calib
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QProgressBar *progressBar;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_1;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *calib)
    {
        if (calib->objectName().isEmpty())
            calib->setObjectName(QStringLiteral("calib"));
        calib->resize(939, 822);
        gridLayout = new QGridLayout(calib);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new QGraphicsView(calib);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 3);

        progressBar = new QProgressBar(calib);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 1, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(412, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        pushButton_1 = new QPushButton(calib);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));

        gridLayout->addWidget(pushButton_1, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(411, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        pushButton_2 = new QPushButton(calib);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 3, 1, 1, 1);

        pushButton_3 = new QPushButton(calib);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 4, 1, 1, 1);


        retranslateUi(calib);

        QMetaObject::connectSlotsByName(calib);
    } // setupUi

    void retranslateUi(QDialog *calib)
    {
        calib->setWindowTitle(QApplication::translate("calib", "calib", Q_NULLPTR));
        pushButton_1->setText(QApplication::translate("calib", "\346\211\223\345\274\200\347\233\270\346\234\272", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("calib", "\345\274\200\345\247\213\346\240\207\345\256\232", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("calib", "\351\200\200\345\207\272\346\240\207\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class calib: public Ui_calib {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIB_H
