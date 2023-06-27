#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include "FileCopyer.h"
#include "DataVM.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void slotProgressBar(float value);
    void slotCopyFinished();

    void on_pushButtonCanel_clicked(); // 取消复制按钮-点击槽函数

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
