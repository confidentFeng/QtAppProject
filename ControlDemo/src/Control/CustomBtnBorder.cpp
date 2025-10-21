#include "CustomBtnBorder.h"

CustomBtnBorder::CustomBtnBorder(QWidget *parent) : QPushButton(parent)
{
    // 允许选中
    this->setCheckable(true);

    m_NormalBackgroundColor = QColor(219, 219, 219); // 平时的背景颜色
    m_CheckedBackgroundColor = QColor(52, 125, 247); // 选中时的背景颜色
    m_DisabledBackgroundColor = QColor(40, 42, 50); // 禁用时的背景颜色
    m_NormalBorderColor = QColor(219, 219, 219); // 平时的边框颜色
    m_CheckedBorderColor = QColor(52, 125, 247); // 选中时的边框颜色
    m_DisableBorderColor = QColor(40, 42, 50); // 禁用时的边框颜色
    m_TextColor = QColor(255, 255, 255); // 平时的文本颜色
    m_CheckedTextColor = QColor(255, 255, 255); // 选中时的文本颜色
    m_DisabledTextColor = QColor(77, 82, 97); // 禁用时的文本颜色

    m_IconSize = QSize(32, 32); // 图标尺寸
    m_IconSeat = E_ICON_LEFT; // 图标位置

    m_TextPixmapMargin = 4; // 按钮文本的图像边距
    m_TextWidth = 16; // 按钮文本的宽度
    m_TextFont = ""; // 按钮文本的字体family
    m_TextSize = 16; // 按钮文本的字体大小

    m_BorderRadius = 6; // 边框圆角
    m_BorderWidth= 2; // 边框宽度
    m_IconMargin = 8; // 图标边距

#ifdef Q_OS_WIN
    this->setCursor(QCursor(Qt::PointingHandCursor));
#else
    this->setCursor(QCursor(QPixmap(":/Image/Util/icon_cursorHand.png")));
#endif
}

// 设置平时的图标图像
void CustomBtnBorder::setIconPixmap(const QPixmap &pixmap)
{
    m_IconPixmap = pixmap;
}

// 设置选中时的文本颜色
void CustomBtnBorder::setIconPixmapChecked(const QPixmap &pixmap)
{
    m_CheckedIconPixmap = pixmap;
}

// 设置禁用时的边框颜色
void CustomBtnBorder::setIconPixmapDis(const QPixmap &pixmap)
{
    m_DisabledIconPixmap = pixmap;
}

// 设置图标尺寸
void CustomBtnBorder::setIconSize(const QSize &iconSize)
{
    m_IconSize = iconSize;
}

// 设置按钮文本
void CustomBtnBorder::setBtnText(const QString &text)
{
    m_ButtonText = text;
}

// 绘图事件
void CustomBtnBorder::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    paintBackground(&painter);
    paintIcon(&painter);
    paintTextBackground(&painter);
    paintText(&painter);
}

// 绘制背景
void CustomBtnBorder::paintBackground(QPainter * painter)
{
    painter->save();
    QPainterPath path;
    QBrush brush;
    brush.setStyle(Qt::NoBrush);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(m_BorderWidth);
    //整体外框也分别会有三种状态
    if (isChecked())
    {
        brush.setColor(m_CheckedBackgroundColor);
        pen.setColor(m_CheckedBorderColor);
    }
    else if(!isEnabled())
    {
        brush.setColor(m_DisabledBackgroundColor);
        pen.setColor(m_DisableBorderColor);
    }
    else
    {
        brush.setColor(m_NormalBackgroundColor);
        pen.setColor(m_NormalBorderColor);
    }
    painter->setBrush(brush);
    QRect rect = QRect(0,0,this->width(),this->height());
    painter->setPen(pen);
    path.addRoundedRect(rect, m_BorderRadius, m_BorderRadius);
    //设置允许裁剪，让圆角更自然
    painter->setClipPath(path);
    painter->setClipping(true);
    painter->drawPath(path);
    painter->restore();
}

// 绘制图标
void CustomBtnBorder::paintIcon(QPainter *painter)
{
    painter->save();
    int iXpos    = 0;
    int iYpos    = 0;
    QPixmap pixmap;
    if (isChecked())
    {
        pixmap = m_CheckedIconPixmap;
    }
    else if (!isEnabled())
    {
        pixmap = m_DisabledIconPixmap;
    }
    else
    {
        pixmap = m_IconPixmap;
    }
    int offsetWidth = 0;
    int offsetHeight = 0;
    QSize pixmapSize(pixmap.width(), pixmap.height());
    if (pixmap.width() > pixmap.height())
    {
        if (pixmap.width() > m_IconSize.rwidth())
        {
            int temp = m_IconSize.rwidth();
            offsetWidth = pixmap.width() - m_IconSize.rwidth();
            int tem = pixmap.height()-offsetWidth;
            pixmapSize=QSize(temp, tem);
        }
    }
    else if (pixmap.height() > pixmap.width())
    {
        if (pixmap.height() > m_IconSize.height())
        {
            int temp = m_IconSize.rheight();
            offsetHeight = pixmap.height() - m_IconSize.rheight();
            int tem = pixmap.width()-offsetHeight;
            pixmapSize=QSize(tem, temp);
        }
    }
    else
    {
        pixmapSize = QSize(pixmap.width(), pixmap.height());
    }
    switch (m_IconSeat)
    {
        case E_ICON_LEFT:
        {
            iXpos = m_IconMargin + ((m_IconSize.rwidth()- pixmapSize.rwidth()) / 2);
            iYpos = (this->rect().height() - pixmapSize.rheight()) / 2;
            pixmap = pixmap.scaled(pixmapSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            painter->drawPixmap(iXpos, iYpos, pixmapSize.rwidth(), pixmapSize.rheight(), pixmap);
        }
            break;
    }
    painter->restore();
}

// 绘制文本背景
void CustomBtnBorder::paintTextBackground(QPainter * painter)
{
    painter->save();

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    painter->setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    switch (m_IconSeat)
    {
        case E_ICON_LEFT:
        {
            int posX = m_IconSize.rwidth()+(2*m_IconMargin);
            int posY = m_TextPixmapMargin ;

            int textPixmapWidth = this->width()-m_IconSize.rwidth()-(2*m_IconMargin)-m_TextPixmapMargin;
            int textPixmapHeight = this->height()-(2*m_TextPixmapMargin);
            m_TextPixmapRect = QRectF(posX, posY, textPixmapWidth, textPixmapHeight);
            path.addRoundedRect(m_TextPixmapRect, m_BorderRadius, m_BorderRadius);
            //设置允许裁剪，让圆角更自然
            painter->setClipPath(path);
            painter->setClipping(true);
        }
            break;
    }
    painter->setPen(Qt::NoPen);

    if (isChecked())
    {
        brush.setColor(m_CheckedBackgroundColor);
    }
    else if(!isEnabled())
    {
        brush.setColor(m_DisabledBackgroundColor);
    }
    else
    {
        brush.setColor(m_NormalBackgroundColor);
    }

    painter->fillPath(path, brush);

    painter->drawPath(path);
    painter->restore();
}

// 绘制文本
void CustomBtnBorder::paintText(QPainter * painter)
{
    painter->save();

    painter->setFont(QFont(m_TextFont, m_TextSize)); // 设置字体
    QColor color;
    if (isChecked())
    {
        color = m_CheckedTextColor;
    }
    else if (!isEnabled())
    {
        color = m_DisabledTextColor;
    }
    else
    {
        color = m_TextColor;
    }
    painter->setPen(QPen(color, m_TextWidth, Qt::SolidLine)); // 设置字体颜色
    painter->drawText(m_TextPixmapRect, Qt::AlignHCenter | Qt::AlignVCenter, m_ButtonText); // 画一行文字


    painter->restore();
}
