#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableView>
#include <QStandardItem>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QEvent>
#include <QMenu>
#include <QScrollBar>
#include <QHeaderView>
#include <QKeyEvent>
#include <QTimer>
#include <QProxyStyle>
#include <QDebug>
#include "MyTableView.h"

#define ITEM_HEIGHT 39
#define ITEM_MAX_COUNT 10

// 子类化QProxyStyle，重写pixelMetric函数，已实现内边距（qss设置内边距不生效）
class TableItemSpaceStyleName : public QProxyStyle
{
public:
    explicit TableItemSpaceStyleName(QWidget *parent = nullptr) { Q_UNUSED(parent); };
    int pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
    {
        switch (metric) {
            case PM_FocusFrameHMargin:
            return 6;
            default:
            break;
        }
        return QProxyStyle::pixelMetric(metric, option, widget);
    }
};

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event); // 键盘按下事件

private:
    void initTableView(); // 初始化QTableView
    void addItem(QString name); // 添加项
    void getMultiCheckItem(); // 获取多选的item
    int getViewFirstNumber(); // 获取viewPort当前显示的可见的第一行
    int getViewLastNumber(); // 获取viewPort当前显示的可见的最后一行

    MyTableView *m_pMyTableView;
    QPushButton *m_pBtnRemove;
    QPushButton *m_pBtnAdd;

    QAction *m_actionAdd;
    QAction *m_actionDel;
    QMenu *m_popMenu; // 右键菜单

    QTimer *m_pTimerMouseOut; // 鼠标双击超时检测定时器
    int m_nCntDouble = 0; // 按键计数
    QString m_userClicked = ""; // 第一次点击对应的用户

    int m_curScrollPos = 0; // 翻页时的当时滑动条位置
    int m_pageHeight = 39*10; // 一页的高度（39为一行的高度，10为一页的行数）
};
#endif // WIDGET_H
