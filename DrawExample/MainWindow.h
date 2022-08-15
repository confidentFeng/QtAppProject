#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QGradient>
#include <QColorDialog>
#include "PaintArea.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    PaintArea *m_paintArea; // 绘图区域类对象

    QLabel *penWidthLabel;
    QSpinBox *penWidthSpinBox;
    QLabel *penColorLabel;
    QFrame *penColorFrame;
    QPushButton *penColorBtn;
    QLabel *penStyleLabel;
    QComboBox *penStyleComboBox;
    QPushButton *m_pBtnClear;

    QGridLayout *rightLayout;

protected slots:
    void slotShape(int); // 形状
    void slotPenColor(); // 画笔颜色
    void slotPenWidth(int); // 画笔宽度
    void slotPenStyle(int); // 画笔风格
    void slotClear(); // 清空绘图区域
};

#endif // MAINWINDOW_H
