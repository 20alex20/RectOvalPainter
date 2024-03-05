#include "window.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
    QApplication appl(argc, argv);
    Window win;
    win.show();
    return appl.exec();
}
