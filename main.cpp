#include "frm_main.h"
#include "frm_about.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    frm_Main window_main;
    window_main.show();

    return a.exec();
}
