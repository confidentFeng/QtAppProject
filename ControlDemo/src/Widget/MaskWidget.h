#ifndef MASKWIDGET_H
#define MASKWIDGET_H

#include <QWidget>
#include <QApplication>
#include <QEvent>

// 弹窗遮罩层
class MaskWidget : public QWidget
{
    Q_OBJECT

public:
    MaskWidget(QWidget *parent = nullptr);

    void installWidget(QWidget *widget); // 注册要显示在遮罩中的窗口
    void setMaskColor(const QColor &color,float opacity); // 设置遮罩颜色、透明度
    void setTopWidget(QWidget *widget); // 设置顶层窗口

private:
    void showEvent(QShowEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QWidget *m_topWidget;    // 顶层窗口，设置遮罩颜色、透明度
    QWidget *m_widget;       // 遮罩中显示的窗口
};


#endif // MASKWIDGET_H
