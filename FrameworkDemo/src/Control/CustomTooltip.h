#ifndef _CustomTooltip_H_
#define _CustomTooltip_H_

#include <QWidget>
#include <QLabel>
#include <QDebug>

class CustomTooltip :public QLabel
{
    Q_OBJECT

public:
    static CustomTooltip &Instance(); // 单例模式
    int getWidth(QString text); // 获取宽度
    void SetToolTip(const QString &text, QPoint point); // 设置提示文本
    void hideWin(); // 隐藏界面

private:
    CustomTooltip();
    ~CustomTooltip();
};

#endif // _CustomTooltip_H_
