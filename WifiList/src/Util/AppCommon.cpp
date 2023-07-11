#include "AppCommon.h"

AppCommon::AppCommon()
{

}

void AppCommon::sleep(unsigned long msec)
{
    QTime deiTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < deiTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void AppCommon::sleepEvent(unsigned long msec)
{
    QEventLoop loop; // 定义一个新的事件循环(对GUI阻塞更有效)
    QTimer::singleShot(msec, &loop, SLOT(quit())); // 创建单次定时器，槽函数为事件循环的退出函数
    loop.exec(); // 事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}

// 设置鼠标坐标
void AppCommon::setMousePos(int x, int y)
{
    QCursor::setPos(x, y);
}

// uint8转uint16
uint16_t AppCommon::u8ToU16(uint8_t high, uint8_t low)
{
    uint16_t number = high<<8 | low;

    return number;
}

// uint16转uint8
QString AppCommon::u16ToU8(uint16_t &num)
{
    uint8_t high = (num >>8)&0xFF;  //高8位
    uint8_t low = (num&0xFF);  //低8位

    return QString::number(high) + "," + QString::number(low);
}

// 执行CMD命令
QString AppCommon::ExecuteCmd(const QString& strCmd)
{
    QProcess cmd;
    cmd.start(strCmd);
    cmd.waitForStarted();
    cmd.waitForFinished();
    return QString::fromLocal8Bit(cmd.readAllStandardOutput());
}
