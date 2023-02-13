/********************************************************************************
** Form generated from reading UI file 'face_detect.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACE_DETECT_H
#define UI_FACE_DETECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_face_detect
{
public:
    QGridLayout *gridLayout;
    QFrame *line;
    QGraphicsView *main_graphicsView;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *offline_det_btn;
    QPushButton *online_det_btn;
    QPushButton *offline_reg_btn;
    QPushButton *online_reg_btn;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QRadioButton *local_radioButton;
    QRadioButton *astra_radioButton;
    QRadioButton *radioButton;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QRadioButton *offline_radioButton;
    QRadioButton *live_radioButton;
    QRadioButton *feature_radioButton;
    QWidget *tab_3;
    QGridLayout *gridLayout_5;
    QPushButton *admin_btn;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEdit;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_6;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *num_label;
    QPushButton *del_btn;
    QPushButton *rename_btn;

    void setupUi(QDialog *face_detect)
    {
        if (face_detect->objectName().isEmpty())
            face_detect->setObjectName(QString::fromUtf8("face_detect"));
        face_detect->resize(1060, 897);
        gridLayout = new QGridLayout(face_detect);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        line = new QFrame(face_detect);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color: rgb(239, 41, 41);\n"
"background-color: rgb(239, 41, 41);"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 2, 0, 1, 1);

        main_graphicsView = new QGraphicsView(face_detect);
        main_graphicsView->setObjectName(QString::fromUtf8("main_graphicsView"));
        main_graphicsView->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(main_graphicsView, 1, 0, 1, 1);

        groupBox = new QGroupBox(face_detect);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(0, 200));
        groupBox->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        offline_det_btn = new QPushButton(groupBox);
        offline_det_btn->setObjectName(QString::fromUtf8("offline_det_btn"));

        gridLayout_2->addWidget(offline_det_btn, 0, 1, 1, 1);

        online_det_btn = new QPushButton(groupBox);
        online_det_btn->setObjectName(QString::fromUtf8("online_det_btn"));

        gridLayout_2->addWidget(online_det_btn, 1, 1, 1, 1);

        offline_reg_btn = new QPushButton(groupBox);
        offline_reg_btn->setObjectName(QString::fromUtf8("offline_reg_btn"));

        gridLayout_2->addWidget(offline_reg_btn, 2, 1, 1, 1);

        online_reg_btn = new QPushButton(groupBox);
        online_reg_btn->setObjectName(QString::fromUtf8("online_reg_btn"));

        gridLayout_2->addWidget(online_reg_btn, 3, 1, 1, 1);

        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        local_radioButton = new QRadioButton(tab);
        local_radioButton->setObjectName(QString::fromUtf8("local_radioButton"));

        gridLayout_3->addWidget(local_radioButton, 0, 0, 1, 1);

        astra_radioButton = new QRadioButton(tab);
        astra_radioButton->setObjectName(QString::fromUtf8("astra_radioButton"));

        gridLayout_3->addWidget(astra_radioButton, 0, 1, 1, 1);

        radioButton = new QRadioButton(tab);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setEnabled(false);

        gridLayout_3->addWidget(radioButton, 0, 2, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        offline_radioButton = new QRadioButton(tab_2);
        offline_radioButton->setObjectName(QString::fromUtf8("offline_radioButton"));

        gridLayout_4->addWidget(offline_radioButton, 0, 0, 1, 1);

        live_radioButton = new QRadioButton(tab_2);
        live_radioButton->setObjectName(QString::fromUtf8("live_radioButton"));

        gridLayout_4->addWidget(live_radioButton, 0, 1, 1, 1);

        feature_radioButton = new QRadioButton(tab_2);
        feature_radioButton->setObjectName(QString::fromUtf8("feature_radioButton"));

        gridLayout_4->addWidget(feature_radioButton, 0, 2, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_5 = new QGridLayout(tab_3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        admin_btn = new QPushButton(tab_3);
        admin_btn->setObjectName(QString::fromUtf8("admin_btn"));

        gridLayout_5->addWidget(admin_btn, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_4, 1, 1, 1, 1);

        lineEdit = new QLineEdit(tab_3);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEchoMode(QLineEdit::Password);

        gridLayout_5->addWidget(lineEdit, 0, 1, 1, 3);

        tabWidget->addTab(tab_3, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 4, 1);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setEnabled(false);
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_6->addWidget(comboBox, 0, 0, 1, 2);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_6->addWidget(label, 2, 0, 1, 1);

        num_label = new QLabel(groupBox_2);
        num_label->setObjectName(QString::fromUtf8("num_label"));
        QFont font;
        font.setPointSize(50);
        font.setBold(true);
        font.setWeight(75);
        num_label->setFont(font);
        num_label->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(num_label, 2, 1, 1, 1);

        del_btn = new QPushButton(groupBox_2);
        del_btn->setObjectName(QString::fromUtf8("del_btn"));

        gridLayout_6->addWidget(del_btn, 1, 1, 1, 1);

        rename_btn = new QPushButton(groupBox_2);
        rename_btn->setObjectName(QString::fromUtf8("rename_btn"));

        gridLayout_6->addWidget(rename_btn, 1, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 0, 2, 4, 1);


        gridLayout->addWidget(groupBox, 3, 0, 1, 1);


        retranslateUi(face_detect);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(face_detect);
    } // setupUi

    void retranslateUi(QDialog *face_detect)
    {
        face_detect->setWindowTitle(QCoreApplication::translate("face_detect", "\344\272\272\350\204\270\350\257\206\345\210\253", nullptr));
        groupBox->setTitle(QString());
        offline_det_btn->setText(QCoreApplication::translate("face_detect", "\347\246\273\347\272\277\346\243\200\346\265\213", nullptr));
        online_det_btn->setText(QCoreApplication::translate("face_detect", "\345\234\250\347\272\277\346\243\200\346\265\213-\345\274\200\345\220\257", nullptr));
        offline_reg_btn->setText(QCoreApplication::translate("face_detect", "\347\246\273\347\272\277\346\263\250\345\206\214", nullptr));
        online_reg_btn->setText(QCoreApplication::translate("face_detect", "\345\234\250\347\272\277\346\263\250\345\206\214", nullptr));
        local_radioButton->setText(QCoreApplication::translate("face_detect", "\346\234\254\345\234\260\347\233\270\346\234\272", nullptr));
        astra_radioButton->setText(QCoreApplication::translate("face_detect", "\344\271\220\350\247\206\344\270\211\345\220\210\344\270\200\347\233\270\346\234\272", nullptr));
        radioButton->setText(QCoreApplication::translate("face_detect", "\345\205\266\344\273\226", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("face_detect", "\347\233\270\346\234\272", nullptr));
        offline_radioButton->setText(QCoreApplication::translate("face_detect", "\347\246\273\347\272\277\350\257\206\345\210\253", nullptr));
        live_radioButton->setText(QCoreApplication::translate("face_detect", "\346\264\273\344\275\223\350\257\206\345\210\253", nullptr));
        feature_radioButton->setText(QCoreApplication::translate("face_detect", "\347\211\271\345\276\201\350\257\206\345\210\253", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("face_detect", "\345\212\237\350\203\275\351\200\211\351\241\271", nullptr));
        admin_btn->setText(QCoreApplication::translate("face_detect", "\347\256\241\347\220\206\345\221\230\347\231\273\345\275\225", nullptr));
        lineEdit->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("face_detect", "\346\263\250\345\206\214\346\237\245\350\257\242", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("face_detect", "\347\211\271\345\276\201\345\272\223", nullptr));
        label->setText(QCoreApplication::translate("face_detect", "\347\211\271\345\276\201\346\225\260\351\207\217:", nullptr));
        num_label->setText(QString());
        del_btn->setText(QCoreApplication::translate("face_detect", "\345\210\240\351\231\244", nullptr));
        rename_btn->setText(QCoreApplication::translate("face_detect", "\346\233\264\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class face_detect: public Ui_face_detect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACE_DETECT_H
