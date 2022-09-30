#ifndef GET_DEVICEWIDGET_H
#define GET_DEVICEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QScrollBar>
#include <QProxyStyle>
#include <QPaintEvent>
#include <QPainter>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QDebug>

#define ITEM_HEIGHT_MATRIX 30 // QTableView的项高度

// 子类化QProxyStyle，重写pixelMetric函数，已实现内边距（qss设置内边距不生效）
class TableItemSpaceStyle : public QProxyStyle
{
public:
    explicit TableItemSpaceStyle(QWidget *parent = nullptr, int space = 15) { Q_UNUSED(parent); m_space = space;};
    int pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
    {
        switch (metric) {
            case PM_FocusFrameHMargin:
            return m_space;
            default:
            break;
        }
        return QProxyStyle::pixelMetric(metric, option, widget);
    }

    int m_space;
};

class MyTableView : public QTableView
{
    Q_OBJECT
public:
    explicit MyTableView(QWidget *parent = nullptr);
    QStandardItemModel *getModel(); // 获取model
    QSortFilterProxyModel *getFilterModel(); // 获取FilterModel
    void searchAndFilter(const QString &sKeyword); // 本地搜索并过滤
    void searchAndSel(const QString &sKeyword); // 本地搜索并选择
    QModelIndex hoverIndex() const { return model()->index(mHoverRow, mHoverColumn); }
    void setHoverColor(const QBrush& brush); // 设置悬浮颜色
    void setEnabled(bool enabled); // 设置使能

protected:
    void mousePressEvent(QMouseEvent *event); // 鼠标点击事件
    void mouseMoveEvent(QMouseEvent *event); // 鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QStandardItemModel *m_pStandModel; // 标准项模型
    QSortFilterProxyModel *m_pFilterModel; // 过滤代理模型
    QPoint m_startPos; // 拖拽开始点击坐标

    int mHoverRow;
    int mHoverColumn;
};

#endif // GET_DEVICEWIDGET_H
