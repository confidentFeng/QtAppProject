#include "CarouselWidget.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QButtonGroup>

const uint TIMER_CHANGE_INTERVAL = 5000;
const uint TIMER_ANIMATION_CHANGE_INTERVAL = 2000;

CarouselWidget::CarouselWidget(QWidget *parent) : QWidget(parent)
{
    m_pTimerImageChange = NULL;
    m_pAnimationOpacity = NULL;
    m_nCurrentImageIndex = 0;

    this->setObjectName("CarouselPane");

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "userpane");

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
}

void CarouselWidget::SetImageList(QStringList listImgFileName)
{
    m_listImgFileName = listImgFileName;
}

void CarouselWidget::StartPlay()
{
    UpdateChangeBtns();
    if (m_listImgFileName.count() == 1)
    {
        m_listBtns[m_nCurrentImageIndex]->setChecked(true);
    }
    else if (m_listImgFileName.count() > 1)
    {
        m_listBtns[m_nCurrentImageIndex]->setChecked(true);
        m_pixCurrent = QPixmap(m_listImgFileName.at(m_nCurrentImageIndex));
        m_pTimerImageChange->start(TIMER_CHANGE_INTERVAL);
        update();
    }
}

void CarouselWidget::CreateAllChildWnd()
{
    m_pTimerImageChange = new QTimer(this);
}

void CarouselWidget::InitCtrl()
{
    // 添加ImageOpacity属性;
    this->setProperty("ImageOpacity", 1.0);

    // 动画切换类;
    m_pAnimationOpacity = new QPropertyAnimation(this, "ImageOpacity");
    // 这里要设置的动画时间小于图片切换时间;
    m_pAnimationOpacity->setDuration(TIMER_ANIMATION_CHANGE_INTERVAL);

    // 设置ImageOpacity属性值的变化范围;
    m_pAnimationOpacity->setStartValue(1.0);
    m_pAnimationOpacity->setEndValue(0.0);
    // 透明度变化及时更新绘图;
    connect(m_pAnimationOpacity, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
}

void CarouselWidget::InitSolts()
{
    connect(m_pTimerImageChange, SIGNAL(timeout()), this, SLOT(OnImageChangeTimeout()));
}

void CarouselWidget::Relayout()
{

}

void CarouselWidget::UpdateChangeBtns()
{
    QButtonGroup* changeButtonGroup = new QButtonGroup;

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addStretch();

    m_listBtns.clear();
    for (int i = 0; i < m_listImgFileName.count(); i++)
    {
        QPushButton *pButton = new QPushButton;
        //pButton->setFixedSize(QSize(16, 16));
        pButton->setCheckable(true);
        pButton->setObjectName("CarouselPane_Btn");
        pButton->setProperty("CarouselPane", "true");

        changeButtonGroup->addButton(pButton, i);
        m_listBtns.append(pButton);
        hLayout->addWidget(pButton);
    }
    hLayout->addStretch();
    hLayout->setSpacing(10);
    hLayout->setMargin(0);

    connect(changeButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(OnImageSwitchButtonClicked(int)));

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(hLayout);
    mainLayout->setContentsMargins(0, 0, 0, 20);
}

void CarouselWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QRect imageRect = this->rect();

    if (m_listImgFileName.count() == 1)
    {
        QPixmap backPixmap = QPixmap(m_listImgFileName.first());
        painter.drawPixmap(imageRect, backPixmap.scaled(imageRect.size()));
    }
    else if (m_listImgFileName.count() > 1)
    {
        float imageOpacity = this->property("ImageOpacity").toFloat();
        painter.setOpacity(1);
        painter.drawPixmap(imageRect, m_pixNext.scaled(imageRect.size()));
        painter.setOpacity(imageOpacity);
        painter.drawPixmap(imageRect, m_pixCurrent.scaled(imageRect.size()));
    }
}

void CarouselWidget::OnImageChangeTimeout()
{
    m_pixCurrent = QPixmap(m_listImgFileName.at(m_nCurrentImageIndex));
    m_nCurrentImageIndex++;
    if (m_nCurrentImageIndex >= m_listImgFileName.count())
    {
        m_nCurrentImageIndex = 0;
    }

    m_pixNext = QPixmap(m_listImgFileName.at(m_nCurrentImageIndex));
    m_listBtns[m_nCurrentImageIndex]->setChecked(true);

    m_pAnimationOpacity->start();
}

void CarouselWidget::OnImageSwitchButtonClicked(int nIndex)
{
    m_nCurrentImageIndex = nIndex - 1;
    if (m_nCurrentImageIndex < 0)
    {
        m_nCurrentImageIndex = m_listImgFileName.count() - 1;
    }

    OnImageChangeTimeout();
    m_pTimerImageChange->start(TIMER_CHANGE_INTERVAL);
    update();
}
