#include "mainwindow.h"
#include <QApplication>
#include "database_xml.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection()||!createXml())
        return 0;

    MainWindow w;
    w.show();

    return a.exec();
}
