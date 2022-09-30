#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QTabWidget>
#include <QTabBar>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QProxyStyle>
#include <QPainter>

// 自定义TabBar样式，以实现TabBar的文本左对齐
class CustomTabStyle : public QProxyStyle
{
public:
    void drawItemText(QPainter* painter, const QRect& rectangle, int alignment,
                      const QPalette& palette, bool enabled, const QString& text,
                      QPalette::ColorRole textRole ) const
    {
        painter->save();
        alignment = Qt::AlignLeft | Qt::AlignVCenter;
        painter->translate(0, 0);
        QCommonStyle::drawItemText(painter, rectangle,
                              alignment,
                              palette,
                              enabled,
                              text,
                              textRole );

        painter->restore();
    }
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

private:
    QTabWidget *m_pTabWidget; // 选项卡界面
    QPushButton *m_pBtnHideTab; // 隐藏选项卡界面按钮
    QWidget *m_pWidget1; // 子界面1
    QWidget *m_pWidget2; // 子界面2
    QWidget *m_pWidget3; // 子界面3
};
#endif // WIDGET_H
