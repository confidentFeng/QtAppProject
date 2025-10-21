#include "ChatRoom.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 应用全局加载样式表
    QFile qss(":/style.qss");
    if (qss.open(QFile::ReadOnly))
    {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
    else{
        qDebug("Open qss failed");
    }

    MeetChatRoom w;
    w.show();

    return a.exec();
}
