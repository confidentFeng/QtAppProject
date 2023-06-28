#include "showmap.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShowMap w;
    w.show();

    return a.exec();
}
