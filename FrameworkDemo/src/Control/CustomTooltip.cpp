#include "CustomTooltip.h"

CustomTooltip::CustomTooltip()
{
    // 初始化界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAlignment(Qt::AlignCenter);
    this->setAttribute(Qt::WA_TransparentForMouseEvents);               //TODO: 2022.10.27 - 设置鼠标穿透属性
    this->setObjectName("CustomTooltip");
    this->setStyleSheet(QString("QWidget#CustomTooltip{background: white;color:black;font-size:14px;border:1px solid black;border-radius:4px;}"));
}

CustomTooltip::~CustomTooltip()
{
    this->deleteLater();
}

// 设置提示文本
void CustomTooltip::SetToolTip(const QString &text, QPoint point)
{
    if (text.isEmpty())
        return;

    // 根据文本内容，自适应宽高
    QFontMetrics fm1(font());
    this->setFixedSize(fm1.width(text) + 20, 24);

    this->setText(text);
    this->move(point);
    this->show();
}

// 隐藏界面
void CustomTooltip::hideWin()
{
    this->hide();
}

// 单例模式
CustomTooltip &CustomTooltip::Instance()
{
    static CustomTooltip tipWidget;
    return tipWidget;
}

// 获取宽度
int CustomTooltip::getWidth(QString text)
{
    // 根据文本内容，自适应宽高
    QFontMetrics fm1(font());
    this->setFixedSize(fm1.width(text) + 20, 24);

    return this->width();
}
