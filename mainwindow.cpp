#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "virtualkeyboard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vb_=new VirtualKeyBoard(this);
    vb_->setGeometry(500,0,800,400);//高度：宽度2：1好看一点
    vb_->hide();
    vb_->setAutoShow(ui->lineEdit_2);//自定义的lineedit
    vb_->setAutoShow(ui->textEdit);//自定义的textEdit

}

MainWindow::~MainWindow()
{
    delete vb_;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(vb_->isHidden())
    {
      vb_->show();
    }else
    {
        vb_->hide();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    vb_->setAutoHide(false);
}

void MainWindow::on_pushButton_3_clicked()
{
    vb_->setAutoHide(true);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        qDebug() << "mouse" ;
        vb_->setAutoHide(true);
    }
}
