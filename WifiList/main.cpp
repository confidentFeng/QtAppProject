#include "src/Wifi/WifiList.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 全局程序初始化类 AppInit 用来做一些程序启动后的初始化处理
    AppInit::Instance()->start();

    WifiList w;
    w.show();

    return a.exec();
}
