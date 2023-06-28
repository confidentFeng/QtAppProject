#include "mainwindow.h"
#include <QApplication>
//#include "other/func.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //setFontPath(":/font.ttf");//解决中文乱码,注意到func.h设置是QT5(较高的不会乱码显示) 还是QT4
    MainWindow w;
    w.show();

    return a.exec();
}
