#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 初始化串口
    m_serial = new Serial;
    // 寻找可用串口
    QStringList serialStrList;
    serialStrList = m_serial->scanSerial();
    for (int i=0; i<serialStrList.size(); i++)
    {
        ui->portComboBox->addItem(serialStrList[i]); // 在comboBox那添加串口号
    }
    // 默认设置波特率为115200（第5项）
    ui->baudComboBox->setCurrentIndex(5);
    // 当下位机中有数据发送过来时就会响应这个槽函数
    connect(m_serial, SIGNAL(readSignal()), this, SLOT(readSerialData()));
}

Widget::~Widget()
{
    delete ui;
}

// 打开串口按钮-点击槽函数
void Widget::on_openPortButton_clicked()
{
    if(ui->openPortButton->text() == tr("打开串口"))
    {
        if(m_serial->open(ui->portComboBox->currentText(), ui->baudComboBox->currentText().toInt()))
        {
            // 关闭下拉列表使能
            ui->portComboBox->setEnabled(false);
            ui->baudComboBox->setEnabled(false);
            // 修改按钮名称
            ui->openPortButton->setText(tr("关闭串口"));
        }
    }
    else
    {
        // 关闭串口
        m_serial->close();
        // 重新开启下拉列表使能
        ui->portComboBox->setEnabled(true);
        ui->baudComboBox->setEnabled(true);
        // 恢复按钮名称
        ui->openPortButton->setText(tr("打开串口"));
    }
}

// 清除接收文本框按钮-点击槽函数
void Widget::on_clearTextButton_clicked()
{
    ui->recvTextEdit->clear();
}

// 清除发送文本框按钮-点击槽函数
void Widget::on_clearSendButton_clicked()
{
    ui->sendTextEdit->clear();
}

// 发送数据按钮-点击槽函数
void Widget::on_sendButton_clicked()
{
    QByteArray sendData = m_serial->hexStringToByteArray(ui->sendTextEdit->toPlainText());
    m_serial->sendData(sendData);
}

// 读取从自定义串口类获得的数据
void Widget::readSerialData()
{
    QString originStr = ui->recvTextEdit->toPlainText(); // 保存接收文本框原本的数据
    ui->recvTextEdit->clear();
    ui->recvTextEdit->setText(originStr);
    ui->recvTextEdit->moveCursor(QTextCursor::End); // 在末尾移动光标一格
    ui->recvTextEdit->insertPlainText(m_serial->getReadBuf().toHex(' ')); // 插入新读取数据（中间以一格空格间隔）
    ui->recvTextEdit->moveCursor(QTextCursor::End); // 在末尾移动光标一格
    ui->recvTextEdit->insertPlainText(" ");

    m_serial->clearReadBuf(); // 读取完后，清空数据缓冲区
}
