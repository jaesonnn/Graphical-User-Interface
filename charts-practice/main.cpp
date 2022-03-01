#include "chartmenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    chartMenu w;
    w.show();
    return a.exec();
}
