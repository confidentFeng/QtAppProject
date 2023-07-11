#include "LoadingWidget.h"

LoadingWidget::LoadingWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);//无边框
    this->setObjectName("LoadingWidget");
    this->setStyleSheet("QWidget#LoadingWidget{background: grey;}");
    this->setAttribute(Qt::WA_StyledBackground);
    this->setProperty("canMove", true);

    m_pLoadingLabel = new QLabel;

    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pLoadingLabel, 0, Qt::AlignCenter);
    pLayoutMain->addStretch();
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);

    m_pAnimation = new QPropertyAnimation(this, "pixmap");
    m_pAnimation->setDuration(1000);
    // 永远运行，直到stop
    m_pAnimation->setLoopCount(-1);

    // 设置动画各区间的值
    for (int i = 0; i < 8; ++i)
    {
        m_pAnimation->setKeyValueAt(i/7.0, i + 1);
    }

    // 开始动画
    startAnimation();
}

// 开始动画
void LoadingWidget::startAnimation()
{
    m_pAnimation->start();
}

// 停止动画
void LoadingWidget::stopAnimation()
{
    m_pAnimation->stop();
}

// 获取图像序号
int LoadingWidget::pixmap() const
{
    return m_nIndex;
}

// 切换图标
void LoadingWidget::setPixmap(const int &index)
{
    m_nIndex = index;

    QPixmap pixmap(m_pixmapPath + QString("%1").arg(index));
    m_pLoadingLabel->setPixmap(pixmap);
}

// 设置图像路径
void LoadingWidget::setPixmapPath(const QString &pixmapPath, int pixmapCnt)
{
    m_pixmapPath = pixmapPath;
    m_pixmapCnt = pixmapCnt;
}
