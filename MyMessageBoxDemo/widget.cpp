#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    // 创建消息提示框实例指针
    MyMessageBox *msgBox = new MyMessageBox();
    // 显示消息提示框
    if(msgBox->showMyMessageBox(this, tr("警告"), tr("您确定要删除该文件吗？"), MESSAGE_WARNNING, \
                                BUTTON_OK_AND_CANCEL, true) == ID_OK)
    {
        qDebug() << "按下了确定按钮";
    }
}
