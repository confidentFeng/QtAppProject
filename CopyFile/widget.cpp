#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置进度条
    ui->progressBar_copy->setValue(0);
    ui->progressBar_copy->setRange(0, 100);

    // 连接信号槽
    connect(DataVM::getInstance(), SIGNAL(sigCopyFileProgress(float)), this, SLOT(slotProgressBar(float)));
    connect(DataVM::getInstance(), SIGNAL(sigAllCopyFilesFinished()), this, SLOT(slotCopyFinished()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    // 获得拷贝视频的路径
    QString fileName = QFileDialog::getOpenFileName(this, tr("文件对话框"), "D:", tr("视频文件(*.mp4)"));
    qDebug() << "fileName: " << fileName;

    QList<QUrl> filePaths;
    filePaths.append(QUrl(fileName));
    filePaths.append(QUrl("C:/Users/Administrator/Videos/record20200328093234.mp4"));
    filePaths.append(QUrl("C:/Users/Administrator/Videos/test222.mp4"));
    DataVM::getInstance()->copyFiles(filePaths, "D:/");
}

void Widget::slotProgressBar(float value)
{
    ui->progressBar_copy->setValue((int)(value*100));

    if(value == 1.0)
        ui->progressBar_copy->setValue(0);
}

// 完成复制
void Widget::slotCopyFinished()
{
    qDebug() << "CopyFinished";
}

// 取消复制按钮-点击槽函数
void Widget::on_pushButtonCanel_clicked()
{
    DataVM::getInstance()->interruptCopyFile();

    ui->progressBar_copy->setValue(0);
}
