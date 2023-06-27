#include "serial.h"

Serial::Serial()
{
    // 初始化串口
    m_serialPort = new QSerialPort;
}

// 扫描可用串口
QStringList Serial::scanSerial()
{
    QStringList serialStrList;

    // 读取串口信息
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        m_serialPort->setPort(info);
        // 判断端口能否以读写方式打开
        if(m_serialPort->open(QIODevice::ReadWrite))
        {
            serialStrList.append(m_serialPort->portName());
            m_serialPort->close(); // 然后自动关闭等待人为开启（通过"打开串口按钮"）
        }
    }

    return serialStrList;
}

// 打开串口
bool Serial::open(QString serialName, int baudRate)
{
    // 设置串口名
    m_serialPort->setPortName(serialName);
    // 打开串口(以读写方式)
    if(m_serialPort->open(QIODevice::ReadWrite))
    {
        m_serialPort->setBaudRate(baudRate); // 设置波特率(默认为115200)
        m_serialPort->setDataBits( QSerialPort::Data8 ); // 设置数据位(数据位为8位)
        m_serialPort->setParity( QSerialPort::NoParity ); // 设置校验位(无校验位)
        m_serialPort->setStopBits( QSerialPort::OneStop ); // 设置停止位(停止位为1)
        m_serialPort->setFlowControl( QSerialPort::NoFlowControl ); // 设置流控制(无数据流控制)

        // 当下位机中有数据发送过来时就会响应这个槽函数
        connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(readData()));
        // 当下位机中有数据发送过来时就会触发这个信号，以提示其它类对象
        connect(m_serialPort, SIGNAL(readyRead()), this, SIGNAL(readSignal()));

        return true;
    }

    return false;
}

// 关闭串口
void Serial::close()
{
    m_serialPort->clear();
    m_serialPort->close();
}

// 发送数据给下位机
void Serial::sendData(QByteArray &sendData)
{
    // 发送数据帧
    m_serialPort->write(sendData);
}

// 读取下位机发来数据
void Serial::readData()
{
    // 将下位机发来数据存储在数据缓冲区
    m_readBuf = m_serialPort->readAll();
}

// 获得读取数据缓冲区
QByteArray Serial::getReadBuf()
{
    return m_readBuf;
}

// 清除读取数据缓冲区
void Serial::clearReadBuf()
{
    m_readBuf.clear();
}

// 将16进制字符串转换为对应的字节序列
QByteArray Serial::hexStringToByteArray(QString HexString)
{
    bool ok;
    QByteArray ret;
    HexString = HexString.trimmed();
    HexString = HexString.simplified();
    QStringList sl = HexString.split(" ");

    foreach (QString s, sl)
    {
        if(!s.isEmpty())
        {
            char c = static_cast<char>(s.toInt(&ok, 16) & 0xFF);
            if(ok)
            {
                ret.append(c);
            }
            else
            {
                qDebug()<<"非法的16进制字符："<<s;
                QMessageBox::warning(nullptr, tr("错误："), QString("非法的16进制字符: \"%1\"").arg(s));
            }
        }
    }

    return ret;
}
