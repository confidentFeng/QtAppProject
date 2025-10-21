#include "CustomBtnSplit.h"

CustomBtnSplit::CustomBtnSplit(QWidget *parent) : QWidget(parent)
{
    // 初始化界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground); // 不继承父窗口样式
    this->setFixedSize(SPLIT_WIDTH/10, SPLIT_HEIGHT/10);
    this->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    this->setObjectName("SplitScrBtn");

    // 初始化颜色
    m_colorPaintBoard = Qt::white;
    m_colorBlue = QColor(0, 147, 221);

    // 删除按钮
    m_pBtnDel = new QPushButton;
    //m_pBtnDel->setFixedSize(26, 26);
    m_pBtnDel->setFixedSize(width(), height());
    m_pBtnDel->setObjectName("SplitScrBtn_BtnDel");
    m_pBtnDel->hide();

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addWidget(m_pBtnDel, 0, Qt::AlignRight);
    pLayoutMain->addStretch();
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);

    // 删除按钮
    connect(m_pBtnDel, &QPushButton::clicked, [=]{
        emit sigDelBtn(); // 删除信号
    });
}

// 是否为默认分屏按钮
void CustomBtnSplit::isDefaultBtn(bool isFixed)
{
    m_isDefaultBtn = isFixed;
}

// 设置网格容器
void CustomBtnSplit::setGridVector(QVector<StGrid> vecRectCell)
{
    m_vecRectCell.clear();
    m_vecRectCell = vecRectCell;
    this->update();
}

QVector<QRect> CustomBtnSplit::getVector()
{
    QVector<QRect> srcVecRect;
    for (auto item: m_vecRectCell) {
        srcVecRect.append(item.rect);
    }

    return srcVecRect;
}

// 设置删除按钮是否可见
void CustomBtnSplit::setDelBtnVisible(bool isVisible)
{
    m_pBtnDel->setVisible(isVisible);
}

// 设置选中状态
void CustomBtnSplit::setChecked(bool isChecked)
{
    m_isChecked = isChecked;

    if(isChecked)
        m_colorPaintBoard = m_colorBlue;
    else
        m_colorPaintBoard = Qt::white;
    this->update();
}

// 获取选中状态
bool CustomBtnSplit::isChecked()
{
    return m_isChecked;
}

// 设置启用状态
void CustomBtnSplit::setEnabled(bool isEnabled)
{
    m_isEnabled = isEnabled;
}

// 获取启用状态
bool CustomBtnSplit::isEnabled()
{
    return m_isEnabled;
}

// 设置分屏模式
void CustomBtnSplit::setSplitMode(EnumSplitMode splitMode)
{
    m_splitMode = splitMode;
}

// 获取分屏模式
EnumSplitMode CustomBtnSplit::getSplitMode()
{
    return m_splitMode;
}

// 绘图事件
void CustomBtnSplit::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(QPen(m_colorPaintBoard));

    //qDebug() << "m_vecRectCell.count: " << m_vecRectCell.count();

    double nX = 0.0;
    double nY = 0.0;
    double nWidth = 0.0;
    double nHeight = 0.0;
    // 绘制各个格子
    for (auto item : m_vecRectCell) {
        painter.setBrush(QBrush(Qt::transparent));

        nX = item.rect.x()/10.0;
        nY = item.rect.y()/10.0;
        nWidth = item.rect.width()/10.0;
        nHeight = item.rect.height()/10.0;

        // 由于宽度为48，不能整除5，导致必须下面这样特殊处理，未找到更好的办法
        /*
        qFloor  4 QRect(0,27 9x9)
        qFloor  5 QRect(9,27 9x9)
        qFloor  6 QRect(19,27 9x9)
        qFloor  7 QRect(28,27 9x9)
        qFloor  8 QRect(38,27 9x9)
        */
        if(nX == 19.2) {
            if(nWidth == 19.2)
                painter.drawRect(qFloor(nX)-1, qFloor(nY), qFloor(nWidth)+1, qFloor(nHeight));
            else if(nWidth == 28.8)
                painter.drawRect(qFloor(nX)-1, qFloor(nY), qFloor(nWidth)+1, qFloor(nHeight));
            else
                painter.drawRect(qFloor(nX)-1, qFloor(nY), qFloor(nWidth), qFloor(nHeight));
        }
        else if(nX == 28.8) {
            painter.drawRect(qFloor(nX)-1, qFloor(nY), qFloor(nWidth)+2, qFloor(nHeight));
        }
        else if(nWidth == 19.2) { // 9.6*2
            if(nX == 0)
                painter.drawRect(qFloor(nX), qFloor(nY), qFloor(nWidth)-1, qFloor(nHeight));
            else if(nX == 9.6)
                painter.drawRect(qFloor(nX), qFloor(nY), qFloor(nWidth)-1, qFloor(nHeight));
            else
                painter.drawRect(qFloor(nX), qFloor(nY), qFloor(nWidth), qFloor(nHeight));
        }
        else if(nWidth == 28.8) { // 9.6*3
            if(nX == 0)
                painter.drawRect(qFloor(nX), qFloor(nY), qFloor(nWidth)-1, qFloor(nHeight));
//            else if(nX == 19.2)
//                painter.drawRect(qFloor(nX), qFloor(nY), qFloor(nWidth)+2, qFloor(nHeight));
            else
                painter.drawRect(qFloor(nX), qFloor(nY), qFloor(nWidth)+1, qFloor(nHeight));
        }
        else {
            painter.drawRect(qFloor(nX), qFloor(nY), qFloor(nWidth), qFloor(nHeight));
        }

//        if(m_vecRectCell.count() == 16)
//            qDebug() << "qFloor " << QRect(qFloor(nX), qFloor(nY), qFloor(nWidth), qFloor(nHeight));
    }

    // 由于实际绘图可见区域为(width()-1, height()-1)，所以要绘制可见区域的下边框线和右边框线
    painter.drawLine(width()-1, 0, width()-1, height()-1);
    painter.drawLine(0, height()-1, width()-1, height()-1);
}

// 鼠标移入事件
void CustomBtnSplit::enterEvent(QEvent *event)
{
    Q_UNUSED(event);

    if(!m_isEnabled)
        return;

    m_colorPaintBoard = m_colorBlue;

    // 更新绘图
    this->update();
}

void CustomBtnSplit::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    if(!m_isEnabled)
        return;

    if(!m_isChecked)
        m_colorPaintBoard = QColor(255, 255, 255);

    // 更新绘图
    this->update();
}

// 鼠标点击事件
void CustomBtnSplit::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    if(!m_isEnabled)
        return;

    m_colorPaintBoard = m_colorBlue;

    if(m_isChecked == false) {
        m_isChecked = true;
        emit sigChecked(m_splitMode); // 选中信号，清除其它分屏的选中状态
        emit clicked(); // 点击信号，设置相应分屏
    }

    this->update();
}
