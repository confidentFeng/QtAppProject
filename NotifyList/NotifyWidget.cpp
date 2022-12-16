#include "NotifyWidget.h"

NotifyWidget::NotifyWidget (QWidget *parent)
    : QWidget(parent) // 这里将manager传入到父类ArrangedWidget中的m_manager了，同时继承了，可以使用父类manager来进行管理
{
    // 初始化界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget | Qt::WindowStaysOnTopHint);
    this->setFixedSize(300, 81); // 高度要是3的倍数，方便鼠标中键滚动正好是一个item
    this->setObjectName("NotifyWidget");
    this->setAttribute(Qt::WA_StyledBackground); // 不继承父窗口样式

    // 初始化图标标签
    m_pLabIcon = new QLabel(this);
    m_pLabIcon->setFixedSize(40, 40);
    m_pLabIcon->setAlignment(Qt::AlignCenter);
    m_pLabIcon->setWordWrap(true);
    // 初始化标题栏标签
    m_pLabTitle = new QLabel(this);
    m_pLabTitle->setObjectName("NotifyWidget_LabTitle");
    // 初始化内容标签
    m_pLabBody = new QLabel(this);
    m_pLabBody->setObjectName("NotifyWidget_LabBody");
    m_pLabBody->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    m_pLabBody->setWordWrap(true);

    // 内容布局
    QVBoxLayout *pLayoutContent = new QVBoxLayout;
    pLayoutContent->addWidget(m_pLabTitle);
    pLayoutContent->addWidget(m_pLabBody);
    pLayoutContent->addStretch();
    // 主布局
    QHBoxLayout *pLayoutMain = new QHBoxLayout(this);
    pLayoutMain->addWidget(m_pLabIcon);
    pLayoutMain->addLayout(pLayoutContent);
    pLayoutMain->setAlignment(m_pLabIcon, Qt::AlignTop);

    // 初始化关闭按钮
    m_pBtnClose = new QPushButton(this);
    m_pBtnClose->setObjectName("NotifyWidget_BtnClose");
    m_pBtnClose->setFixedSize(20, 30);
    m_pBtnClose->move(this->width() - m_pBtnClose->width(), 0);
    connect(m_pBtnClose, &QPushButton::clicked, this, [=]{
        // 移动向右消失动画
        animationMove(this, 200, 300, [=](){
            this->deleteLater();
        });
    });
}

// 设置数据
void NotifyWidget::setData(const QVariantMap &data)
{
    // 设置数据
    m_data = data;

    // 设置默认图标
    m_pLabIcon->setPixmap(QPixmap(data.value("icon").toString()));
    // 显示标题
    m_pLabTitle->setText(data.value("title").toString());
    // 显示内容
    m_pLabBody->setText( m_data.value("body").toString());
}

// 队列中的剩余通知数目
NotifyCountWidget::NotifyCountWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint); // 设置为顶级窗口，为了实现控件的透明度改变动画
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true); // 允许鼠标穿透

    // 初始化图标标签
    m_pLabIcon = new QLabel(this);
    m_pLabIcon->setFixedSize(40, 40);
    m_pLabIcon->setAlignment(Qt::AlignCenter);
    m_pLabIcon->setObjectName("NotifyCountWidget_LabIcon");
    // 初始化数目标签
    m_pLabCount = new QLabel(this);
    m_pLabCount->setObjectName("NotifyCountWidget_LabCount");
    m_pLabCount->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    // 主布局
    QHBoxLayout *pLayoutMain = new QHBoxLayout(this);
    pLayoutMain->addWidget(m_pLabIcon);
    pLayoutMain->addWidget(m_pLabCount);

    // 闪烁动画
    m_pFlickerAnim = new QPropertyAnimation(this, "windowOpacity", this); // 实现控件的透明度设置（不过该属性只能对顶级窗口使用，对普通控件这些无效）
    m_pFlickerAnim->setStartValue(1);
    m_pFlickerAnim->setKeyValueAt(0.25, 0.1);
    m_pFlickerAnim->setKeyValueAt(0.5, 1);
    m_pFlickerAnim->setEndValue(1);
    m_pFlickerAnim->setDuration(2000);
    m_pFlickerAnim->setLoopCount(-1);
}

// 设置通知数目
void NotifyCountWidget::setCount(int count)
{
    m_pLabCount->setNum(count);
}

// 是否开启动画
void NotifyCountWidget::isStartAnim(bool isShow)
{
    if (isShow)
        m_pFlickerAnim->start();
    else
        m_pFlickerAnim->stop();
}
