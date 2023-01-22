#include <QApplication>
//#include "main_window.h"
#include "start_window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
//    main_window m;
//    m.show();
    start_window sw;
    sw.setAttribute(Qt::WA_QuitOnClose, true);
    sw.show();
    return QApplication::exec();
}
