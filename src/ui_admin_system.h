/********************************************************************************
** Form generated from reading UI file 'admin_system.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMIN_SYSTEM_H
#define UI_ADMIN_SYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_admin_system
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label_4;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_5;
    QPushButton *pushButton_1;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_7;
    QLabel *label_1;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_9;
    QSpacerItem *verticalSpacer_10;
    QSpacerItem *verticalSpacer_11;
    QSpacerItem *verticalSpacer_12;

    void setupUi(QDialog *admin_system)
    {
        if (admin_system->objectName().isEmpty())
            admin_system->setObjectName(QStringLiteral("admin_system"));
        admin_system->resize(597, 801);
        gridLayout = new QGridLayout(admin_system);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(612, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 1, 1, 2);

        verticalSpacer = new QSpacerItem(20, 722, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 2, 4, 1);

        verticalSpacer_2 = new QSpacerItem(20, 696, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 3, 1);

        scrollArea = new QScrollArea(admin_system);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 525, 679));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(80, 80));

        gridLayout_2->addWidget(label_2, 3, 1, 1, 1);

        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(80, 80));

        gridLayout_2->addWidget(label_4, 7, 1, 1, 1);

        pushButton_4 = new QPushButton(scrollAreaWidgetContents);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(0, 80));

        gridLayout_2->addWidget(pushButton_4, 7, 2, 1, 1);

        pushButton_2 = new QPushButton(scrollAreaWidgetContents);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(200, 80));
        QFont font;
        font.setFamily(QStringLiteral("Ani"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        pushButton_2->setFont(font);

        gridLayout_2->addWidget(pushButton_2, 3, 2, 1, 1);

        pushButton_3 = new QPushButton(scrollAreaWidgetContents);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(0, 80));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_3->setFont(font1);

        gridLayout_2->addWidget(pushButton_3, 5, 2, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 2, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 3, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 0, 2, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_5, 4, 2, 1, 1);

        pushButton_1 = new QPushButton(scrollAreaWidgetContents);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_1->sizePolicy().hasHeightForWidth());
        pushButton_1->setSizePolicy(sizePolicy);
        pushButton_1->setMinimumSize(QSize(200, 80));
        pushButton_1->setFont(font);
        pushButton_1->setAutoRepeat(false);

        gridLayout_2->addWidget(pushButton_1, 1, 2, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_6, 6, 2, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 8, 2, 1, 1);

        label_1 = new QLabel(scrollAreaWidgetContents);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setMaximumSize(QSize(80, 80));

        gridLayout_2->addWidget(label_1, 1, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 1, 0, 1, 1);

        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(80, 80));

        gridLayout_2->addWidget(label_3, 5, 1, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_8, 0, 1, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_9, 2, 1, 1, 1);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_10, 4, 1, 1, 1);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_11, 6, 1, 1, 1);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_12, 8, 1, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 3, 1, 1, 1);


        retranslateUi(admin_system);

        QMetaObject::connectSlotsByName(admin_system);
    } // setupUi

    void retranslateUi(QDialog *admin_system)
    {
        admin_system->setWindowTitle(QApplication::translate("admin_system", "admin_system", Q_NULLPTR));
        label_2->setText(QApplication::translate("admin_system", "TextLabel", Q_NULLPTR));
        label_4->setText(QApplication::translate("admin_system", "TextLabel", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("admin_system", "\346\234\252\345\274\200\345\217\221", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("admin_system", "\344\272\272\350\204\270\350\257\206\345\210\253", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("admin_system", "\347\233\270\346\234\272\346\240\207\345\256\232", Q_NULLPTR));
        pushButton_1->setText(QApplication::translate("admin_system", "\346\250\241\346\235\277\345\214\271\351\205\215", Q_NULLPTR));
        label_1->setText(QApplication::translate("admin_system", "TextLabel.....", Q_NULLPTR));
        label_3->setText(QApplication::translate("admin_system", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class admin_system: public Ui_admin_system {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMIN_SYSTEM_H
