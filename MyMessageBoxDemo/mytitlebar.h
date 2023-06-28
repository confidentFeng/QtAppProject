/*
* Copyright (c) 2019,浙江智澜科技有限公司
* All rights reserved.
*
* 摘 要：实现自定义标题栏，暂时只用于消息对话框类
*
* 当前版本：1.0
* 作 者：聂咸丰
* 完成日期：2019 年 9 月 3 日
*/
#ifndef MYTITLEBAR_H
#define MYTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>

#define BUTTON_HEIGHT 30		// 按钮高度
#define BUTTON_WIDTH 30			// 按钮宽度
#define TITLE_HEIGHT 30			// 标题栏高度

enum ButtonType
{
    MIN_BUTTON = 0,			// 最小化和关闭按钮
    MIN_MAX_BUTTON ,		// 最小化、最大化和关闭按钮
    ONLY_CLOSE_BUTTON,		// 只有关闭按钮
};

class MyTitleBar : public QWidget
{
    Q_OBJECT

public:
    MyTitleBar(QWidget *parent = nullptr);
    ~MyTitleBar();

    // 设置标题栏背景色
    void setBackgroundColor(int colorR, int colorG, int colorB);
    // 设置标题栏图标
    void setTitleIcon(QString filePath , QSize IconSize = QSize(25 , 25));
    // 设置标题内容
    void setTitleContent(QString titleContent , int titleFontSize = 9);
    // 设置标题栏长度
    void setTitleWidth(int width);
    // 设置标题颜色
    void setTitleColor(int colorR, int colorG, int colorB);
    // 设置标题栏上按钮类型
    void setButtonType(ButtonType buttonType);
    // 设置标题栏中的标题是否会滚动;具体可以看效果
    void setTitleRoll();
    // 设置窗口边框宽度
    void setWindowBorderWidth(int borderWidth);

private:
    // 绘图事件：绘制标题栏背景色
    void paintEvent(QPaintEvent *event);
    // 鼠标双击事件：主要是实现双击标题栏进行最大化和最小化操作
    void mouseDoubleClickEvent(QMouseEvent *event);
    // 以下通过mousePressEvent、mouseMoveEvent、mouseReleaseEvent三个事件实现了鼠标拖动标题栏移动窗口的效果
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    // 初始化控件
    void initControl();
    // 加载本地样式文件：可以将样式直接写在文件中，程序运行时直接加载进来
    void loadStyleSheet(const QString &sheetName);

private slots:
    // 该方法主要是让标题栏中的标题显示为滚动的效果
    void onRollTitle();
    // 进行最小化、最大化/还原、关闭操作
    void onClicked();

private:
    // 标题栏背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;

    QLabel* m_pIcon;					// 标题栏图标
    QLabel* m_pTitleLabel;              // 标题栏标签
    QPushButton* m_pButtonMin;			// 最小化按钮
    QPushButton* m_pButtonRestore;		// 最大化还原按钮
    QPushButton* m_pButtonMax;			// 最大化按钮
    QPushButton* m_pButtonClose;		// 关闭按钮

    bool m_isPressed; // 移动窗口的变量
    QPoint m_startMovePos; // 开始移动窗口的坐标变量
    QString m_titleContent; // 标题栏内容
    ButtonType m_buttonType; // 按钮类型
    QTimer m_titleRollTimer; // 标题栏跑马灯效果时钟
    int m_windowBorderWidth; // 窗口边框宽度
};

#endif // MYTITLEBAR_H
