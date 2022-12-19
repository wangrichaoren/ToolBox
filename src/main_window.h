//
// Created by wrc on 22-12-5.
//

#ifndef TOOLBOX_MAIN_WINDOW_H
#define TOOLBOX_MAIN_WINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class main_window; }
QT_END_NAMESPACE

class main_window : public QWidget {
Q_OBJECT

public:
    explicit main_window(QWidget *parent = nullptr);

    ~main_window() override;

    void clickBtn0();

    void clickBtn1();

    void clickBtn2();

private:
    Ui::main_window *ui;
};


#endif //TOOLBOX_MAIN_WINDOW_H
