#include "HoverDelegate.h"

// 设置使能
void HoverDelegate::setEnabled(bool enabled)
{
    m_isEnabled = enabled;
}

// 设置悬浮颜色
void HoverDelegate::setHoverColor(const QBrush &brush)
{
    m_colorHover = brush;
}

// 绘图事件
void HoverDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    if(opt.state.testFlag(QStyle::State_HasFocus)){
        opt.state = opt.state &~ QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, opt, index);
    if(!m_isEnabled){
        return ;
    }
}

// 初始化样式选项
void HoverDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);
    if(!m_isEnabled){
        return ;
    }

    // 是悬浮状态的行，则设置其的悬浮颜色
    if(isHoveredRow(*option, index)){
        option->backgroundBrush = m_colorHover;

        // 设置前景色、边框颜色等
        //option->palette.setBrush(QPalette::Text, Qt::green);
        //option->palette.setBrush(QPalette::Active, QPalette::Highlight, Qt::green);
        //option->palette.setBrush(QPalette::Active, QPalette::HighlightedText, Qt::red);
    }
}

// 检测是否为悬浮状态的行
bool HoverDelegate::isHoveredRow(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    bool ret = false;
    int gridWidth = 0;
    if(const QTableView* tableView = qobject_cast<const QTableView*>(option.widget)){
        gridWidth = tableView->showGrid() ? 1 : 0;
    }
    for(int i = 0; i < index.model()->columnCount(); ++i){
        QModelIndex idx = index.model()->index(index.row(), i);
        if(const QAbstractItemView* view = qobject_cast<const QAbstractItemView*>(option.widget)){
            QStyleOptionViewItem o;
            o.initFrom(view);
            o.rect = view->visualRect(idx).adjusted(0, 0, gridWidth, gridWidth);
            if(o.rect.contains(view->viewport()->mapFromGlobal(QCursor::pos()))){
                ret = true;
            }
        }
    }

    return ret;
}
