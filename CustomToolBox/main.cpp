#include <QApplication>
#include <QFile>
#include "MainWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载样式表
    QFile qss(":/qss/toolpage.qss");
    if (qss.open(QFile::ReadOnly))
    {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
    else{
        qDebug("Open qss failed");
    }

    MainWindow w;
    w.show();

    return a.exec();
}
