#ifndef CUSTOMBTNBORDER_H
#define CUSTOMBTNBORDER_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPaintDevice>

class CustomBtnBorder : public QPushButton
{
    Q_OBJECT
public:
    enum IconSeat {
        E_ICON_LEFT = 0
    };

    explicit CustomBtnBorder(QWidget *parent = nullptr);
    void setIconPixmap(const QPixmap &pixmap); // 设置平时的图标图像
    void setIconPixmapChecked(const QPixmap &pixmap); // 设置选中时的文本颜色
    void setIconPixmapDis(const QPixmap &pixmap); // 设置禁用时的边框颜色
    void setIconSize(const QSize &iconSize); // 设置图标尺寸
    void setBtnText(const QString &text); // 设置按钮文本

protected:
    void paintEvent(QPaintEvent *event); // 绘图事件

private:
    void paintBackground(QPainter *painter); // 绘制背景
    void paintIcon(QPainter *painter); // 绘制图标
    void paintTextBackground(QPainter *painter); // 绘制文本背景
    void paintText(QPainter *painter); // 绘制文本

    QColor m_NormalBackgroundColor; // 平时的背景颜色
    QColor m_CheckedBackgroundColor; // 选中时的背景颜色
    QColor m_DisabledBackgroundColor; // 禁用时的背景颜色
    QColor m_NormalBorderColor; // 平时的边框颜色
    QColor m_CheckedBorderColor; // 选中时的边框颜色
    QColor m_DisableBorderColor; // 禁用时的边框颜色
    QColor m_TextColor; // 平时的文本颜色
    QColor m_CheckedTextColor; // 选中时的文本颜色
    QColor m_DisabledTextColor; // 禁用时的文本颜色

    QPixmap m_IconPixmap; // 平时的图标图像
    QPixmap m_CheckedIconPixmap; // 选中时的图标图像
    QPixmap m_DisabledIconPixmap; // 禁用时的图标图像
    QSize m_IconSize; // 图标尺寸
    IconSeat m_IconSeat; // 图标位置

    QString m_ButtonText; // 按钮文本
    int m_TextPixmapMargin; // 按钮文本的图像边距
    int m_TextWidth; // 按钮文本的宽度
    QRectF m_TextPixmapRect; // 按钮文本的图像尺寸
    QString m_TextFont; // 按钮文本的字体family
    int m_TextSize; // 按钮文本的字体大小

    int m_BorderRadius; // 边框圆角
    int m_BorderWidth; // 边框宽度
    int m_IconMargin; // 图标边距
};

#endif // CUSTOMBTNBORDER_H
