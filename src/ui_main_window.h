/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_window
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label7;
    QLabel *label8;
    QLabel *label9;
    QLabel *label10;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton1;
    QLabel *label1;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label1_2;
    QSpacerItem *horizontalSpacer_7;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_11;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButton2;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *main_window)
    {
        if (main_window->objectName().isEmpty())
            main_window->setObjectName(QStringLiteral("main_window"));
        main_window->resize(424, 501);
        gridLayout = new QGridLayout(main_window);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(51, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 2);

        label7 = new QLabel(main_window);
        label7->setObjectName(QStringLiteral("label7"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(67);
        sizePolicy.setHeightForWidth(label7->sizePolicy().hasHeightForWidth());
        label7->setSizePolicy(sizePolicy);
        label7->setMinimumSize(QSize(67, 67));
        label7->setMaximumSize(QSize(67, 67));

        gridLayout->addWidget(label7, 0, 2, 1, 1);

        label8 = new QLabel(main_window);
        label8->setObjectName(QStringLiteral("label8"));
        label8->setMaximumSize(QSize(67, 67));

        gridLayout->addWidget(label8, 0, 3, 1, 1);

        label9 = new QLabel(main_window);
        label9->setObjectName(QStringLiteral("label9"));
        label9->setMaximumSize(QSize(67, 67));

        gridLayout->addWidget(label9, 0, 4, 1, 1);

        label10 = new QLabel(main_window);
        label10->setObjectName(QStringLiteral("label10"));

        gridLayout->addWidget(label10, 0, 5, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(51, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 0, 6, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        tabWidget = new QTabWidget(main_window);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        font.setWeight(75);
        tabWidget->setFont(font);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton1 = new QPushButton(tab);
        pushButton1->setObjectName(QStringLiteral("pushButton1"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(170);
        sizePolicy1.setVerticalStretch(80);
        sizePolicy1.setHeightForWidth(pushButton1->sizePolicy().hasHeightForWidth());
        pushButton1->setSizePolicy(sizePolicy1);
        pushButton1->setMaximumSize(QSize(170, 80));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton1->setFont(font1);

        gridLayout_2->addWidget(pushButton1, 3, 2, 1, 1);

        label1 = new QLabel(tab);
        label1->setObjectName(QStringLiteral("label1"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(80);
        sizePolicy2.setVerticalStretch(80);
        sizePolicy2.setHeightForWidth(label1->sizePolicy().hasHeightForWidth());
        label1->setSizePolicy(sizePolicy2);
        label1->setMaximumSize(QSize(80, 80));
        label1->setTextFormat(Qt::AutoText);

        gridLayout_2->addWidget(label1, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 4, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 2, 1, 1);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMaximumSize(QSize(170, 80));
        pushButton->setFont(font1);

        gridLayout_2->addWidget(pushButton, 1, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 2, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 4, 1, 1);

        label1_2 = new QLabel(tab);
        label1_2->setObjectName(QStringLiteral("label1_2"));
        sizePolicy2.setHeightForWidth(label1_2->sizePolicy().hasHeightForWidth());
        label1_2->setSizePolicy(sizePolicy2);
        label1_2->setMaximumSize(QSize(80, 80));

        gridLayout_2->addWidget(label1_2, 3, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 1, 3, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalSpacer_4 = new QSpacerItem(20, 71, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 0, 2, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_11, 1, 0, 1, 1);

        lineEdit = new QLineEdit(tab_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(250);
        sizePolicy3.setVerticalStretch(30);
        sizePolicy3.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy3);
        lineEdit->setMaximumSize(QSize(250, 30));

        gridLayout_3->addWidget(lineEdit, 1, 1, 1, 3);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_12, 1, 4, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_5, 2, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 3, 0, 1, 2);

        pushButton2 = new QPushButton(tab_2);
        pushButton2->setObjectName(QStringLiteral("pushButton2"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(150);
        sizePolicy4.setVerticalStretch(50);
        sizePolicy4.setHeightForWidth(pushButton2->sizePolicy().hasHeightForWidth());
        pushButton2->setSizePolicy(sizePolicy4);
        pushButton2->setMinimumSize(QSize(150, 50));
        pushButton2->setMaximumSize(QSize(150, 50));
        pushButton2->setSizeIncrement(QSize(150, 50));
        pushButton2->setBaseSize(QSize(150, 50));
        QFont font2;
        font2.setPointSize(15);
        pushButton2->setFont(font2);

        gridLayout_3->addWidget(pushButton2, 3, 2, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_10, 3, 3, 1, 2);

        verticalSpacer_6 = new QSpacerItem(20, 71, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_6, 4, 2, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 1, 1, 1, 6);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 7, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 1, 1, 2);


        retranslateUi(main_window);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(main_window);
    } // setupUi

    void retranslateUi(QWidget *main_window)
    {
        main_window->setWindowTitle(QApplication::translate("main_window", "ToolBox", Q_NULLPTR));
        label7->setText(QApplication::translate("main_window", "TextLabel", Q_NULLPTR));
        label8->setText(QApplication::translate("main_window", "TextLabel", Q_NULLPTR));
        label9->setText(QApplication::translate("main_window", "TextLabel", Q_NULLPTR));
        label10->setText(QApplication::translate("main_window", "TextLabel", Q_NULLPTR));
        pushButton1->setText(QApplication::translate("main_window", "\351\200\200\345\207\272", Q_NULLPTR));
        label1->setText(QString());
        pushButton->setText(QApplication::translate("main_window", "\346\226\207\344\273\266\345\212\240\345\257\206\345\212\251\346\211\213", Q_NULLPTR));
        label1_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("main_window", "\346\231\256\351\200\232\346\210\220\345\221\230", Q_NULLPTR));
        pushButton2->setText(QApplication::translate("main_window", "\347\231\273\351\231\206", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("main_window", "\347\256\241\347\220\206\345\221\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class main_window: public Ui_main_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
