//
// Created by wrc on 23-1-22.
//

#ifndef TOOLBOX_START_WINDOW_H
#define TOOLBOX_START_WINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class start_window; }
QT_END_NAMESPACE

class start_window : public QWidget {
Q_OBJECT

public:
    explicit start_window(QWidget *parent = nullptr);

    ~start_window() override;

private:
    Ui::start_window *ui;
};


#endif //TOOLBOX_START_WINDOW_H
