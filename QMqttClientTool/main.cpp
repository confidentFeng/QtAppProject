#include "QMqttClientTool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMqttClientTool w;
    w.show();

    return a.exec();
}
