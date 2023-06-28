#ifndef SHOWMAP_H
#define SHOWMAP_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include "math.h"

#define WINDOW_WIDTH 1024 //窗口宽度
#define WINDOW_HEIGHT 768 //窗口高度

namespace Ui {
class ShowMap;
}

class ShowMap : public QWidget
{
    Q_OBJECT

public:
    explicit ShowMap(QWidget *parent = nullptr);
    ~ShowMap();

private slots:
    void on_addBoardButton_clicked(); //放大背景图按钮-点击槽函
    void on_lessBoardButton_clicked(); //缩小背景图按钮-点击槽函数
    void on_resetBoardButton_clicked(); //复位背景图按钮-点击槽函数
    void doProssTimerOut(); //超时函数：超时后将当前鼠标按下坐标，赋给预设点绘制坐标

    void on_manualButton_clicked(); //手动按钮-点击槽函数
    void on_addItemButton_clicked(); //手动模式添加巡航点按钮-点击槽函数
    void on_cruiseGroupBox_returnBtn_clicked(); //巡航分组框的返回按钮-点击槽函数
    void on_lessItemButton_clicked(); //手动模式删除巡航点按钮-点击槽函数

private:
    Ui::ShowMap *ui;

    //地图相关
    QPixmap pix;
    QPoint OriginSize; //地图图片的尺寸大小
    QPoint CurrImgSize; //地图图片的尺寸大小
    QPoint ImgPaintOrigin; //地图图片的绘制原点
    int AddLessCount; //放大缩小次数

    //设定点相关
    QList<QPoint> Point_xy; //定义设定点列表
    QPoint PreSetPoint_xy; //设定点绘制坐标
    QPoint CentPoint_xy; //地图图片中心点
    QPoint MousePress_xy; //鼠标当前点
    QPoint MapRemov_Old; //鼠标不点击在摇杆大圆内时的鼠标点击坐标
    int MouseAllMove_x; //鼠标全部移动x坐标
    int MouseAllMove_y; //鼠标全部移动y坐标

    QTimer *timer; //预设点设置相关定时器

    void Init(); //初始化窗口
    void paintEvent(QPaintEvent *event); //绘图事件：绘制地图、预设点
    void mousePressEvent(QMouseEvent *e); //鼠标按下事件：获取摇杆所在的实时坐标
    void mouseMoveEvent(QMouseEvent *e); //鼠标移动事件：实现摇杆功能
};

#endif // SHOWMAP_H
