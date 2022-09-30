#ifndef DRAWROWTABLEDELEGATE_H
#define DRAWROWTABLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QTableView>
#include <QPainter>
#include <QDebug>

// 自定义Delegate，为了hover变色
class HoverDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void setEnabled(bool enabled); // 设置使能
    void setHoverColor(const QBrush& brush); // 设置悬浮颜色

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const; // 绘图事件
    virtual void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const; // 初始化样式选项

private:
    bool isHoveredRow(const QStyleOptionViewItem& option, const QModelIndex& index)const; // 检测是否为悬浮状态的行

private:
    bool m_isEnabled = false; // 是否允许使能
    QBrush m_colorForeground;
    QBrush m_colorHover;
};

#endif
