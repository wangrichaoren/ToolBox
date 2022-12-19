//
// Created by wrc on 22-12-8.
//

#ifndef TOOLBOX_ADMIN_SYSTEM_H
#define TOOLBOX_ADMIN_SYSTEM_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class admin_system; }
QT_END_NAMESPACE

class admin_system : public QDialog {
Q_OBJECT

public:
    explicit admin_system(QWidget *parent = nullptr);

    void clickTempleMatchBtn();

    void clickFaceDetBtn();

    ~admin_system() override;

private:
    Ui::admin_system *ui;
};


#endif //TOOLBOX_ADMIN_SYSTEM_H
