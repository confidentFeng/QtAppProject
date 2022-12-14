#include "NotifyWidget.h"
#include "NotifyManager.h"

NotifyWidget::NotifyWidget (NotifyManager *manager, QWidget *parent)
    : ArrangedWidget(manager, parent) // 这里将manager传入到父类ArrangedWidget中的m_manager了，同时继承了，可以使用父类manager来进行管理
{
    // 初始化背景界面
    m_pFrameBack = new QFrame(this);
    m_pFrameBack->setGeometry(3, 3, width()-6, height()-6);
    m_pFrameBack->setObjectName("notify-background");
    // 初始化图标标签
    m_pLabIcon = new QLabel(m_pFrameBack);
    m_pLabIcon->setFixedSize(40, 40);
    m_pLabIcon->setAlignment(Qt::AlignCenter);
    m_pLabIcon->setWordWrap(true);
    // 初始化标题栏标签
    m_pLabTitle = new QLabel(m_pFrameBack);
    m_pLabTitle->setObjectName("notify-title");
    // 初始化内容标签
    m_pLabBody = new QLabel(m_pFrameBack);
    m_pLabBody->setObjectName("notify-body");
    m_pLabBody->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    m_pLabBody->setWordWrap(true);

    // 内容布局
    QVBoxLayout *pLayoutContent = new QVBoxLayout;
    pLayoutContent->addWidget(m_pLabTitle);
    pLayoutContent->addWidget(m_pLabBody);
    pLayoutContent->setStretch(1, 1);
    // 主布局
    QHBoxLayout *pLayoutMain = new QHBoxLayout(m_pFrameBack);
    pLayoutMain->addWidget(m_pLabIcon);
    pLayoutMain->addLayout(pLayoutContent);
    pLayoutMain->setAlignment(m_pLabIcon, Qt::AlignTop);

    // 初始化关闭按钮
    m_pBtnClose = new QPushButton("×", m_pFrameBack);
    m_pBtnClose->setObjectName("notify-close-btn");
    m_pBtnClose->setFixedSize(24, 24);
    m_pBtnClose->move(m_pFrameBack->width() - m_pBtnClose->width(), 0);
    connect(m_pBtnClose, &QPushButton::clicked, this, &QObject::deleteLater);

    // 设置样式
    this->setStyleSheet(m_manager->styleSheet());

#ifdef Q_OS_WIN // linuxFb下，设置边框阴影有问题，故屏蔽
    // 设置边框阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setBlurRadius(5);
    m_pFrameBack->setGraphicsEffect(shadow);
#endif

    // 可见状态改变信号槽
    connect(this, &ArrangedWidget::visibleChanged, [this](bool visible){
        if (visible)
        {
            // 通知显示出来过了displayTime之后隐藏并自动销毁
            int displayTime = m_data.value("displayTime", m_manager->displayTime()).toInt();
            QTimer::singleShot(displayTime, this, [this](){
                showArranged(0); // 隐藏
            });
        }
        else {
            // 不可见，即隐藏了，则自动销毁
            this->deleteLater();
        }
    });
}

// 获取数据
QVariantMap NotifyWidget::data() const
{
    return m_data;
}

// 设置数据
void NotifyWidget::setData(const QVariantMap &data)
{
    m_data = data;

    // 设置默认图标
    QPixmap icon;
    QVariant iconv = data.value("icon");
    if (iconv.type() == QVariant::Pixmap) icon = iconv.value<QPixmap>();
    if (iconv.type() == QVariant::String) icon = QPixmap(iconv.toString());
    else icon = QPixmap(m_manager->defaultIcon());
    icon = icon.scaled(QSize(32, 32), Qt::KeepAspectRatio);
    m_pLabIcon->setPixmap(icon);

    // 设置内容
    QString title = data.value("title").toString();
    m_pLabTitle->setText(title);

    // 计算可显示行数及长度
    QString body = m_data.value("body").toString();
    QSize s1 = m_pLabBody->size();
    QSize s2 = m_pLabBody->fontMetrics().size(Qt::TextSingleLine, body);
    int linecount = s1.height()/s2.height();
    int charcount = qFloor(1.0*body.size()*s1.width()/s2.width()) * linecount;
    QString bodyElid = charcount > body.size() ? body : (body.left(charcount-1)+"…");
    m_pLabBody->setText(bodyElid);

    // 设置样式
    if (data.contains("styleSheet"))
        setStyleSheet(data.value("styleSheet").toString());
    else if (data.contains("theme"))
        setStyleSheet(m_manager->styleSheet(data.value("theme").toString()));
}

// 队列中的剩余通知数目
NotifyCountWidget::NotifyCountWidget(NotifyManager *manager, QWidget *parent)
    : ArrangedWidget(manager, parent)
{
    // 初始化界面
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    // 初始化图标标签
    m_pLabIcon = new QLabel(this);
    m_pLabIcon->setFixedSize(40, 40);
    m_pLabIcon->setAlignment(Qt::AlignCenter);
    // 初始化剩余数目标签
    m_pLabCount = new QLabel(this);
    m_pLabCount->setObjectName("notify-count");
    m_pLabCount->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    // 主布局
    QHBoxLayout *pLayoutMain = new QHBoxLayout(this);
    pLayoutMain->addWidget(m_pLabIcon);
    pLayoutMain->addWidget(m_pLabCount);

    // 文字阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(2, 2);
    shadow->setBlurRadius(5);
    setGraphicsEffect(shadow);

    setStyleSheet("#notify-count {""font: 20px Verdana;""color: #dd424d;""}");

    // 设置图标
    QPixmap icon = QPixmap(m_manager->defaultIcon());
    icon = icon.scaled(QSize(32, 32), Qt::KeepAspectRatio);
    m_pLabIcon->setPixmap(icon);

    // 闪烁动画
    flickerAnim = new QPropertyAnimation(this, "windowOpacity", this);
    flickerAnim->setStartValue(1);
    flickerAnim->setKeyValueAt(0.25, 0.1);
    flickerAnim->setKeyValueAt(0.5, 1);
    flickerAnim->setEndValue(1);
    flickerAnim->setDuration(2000);
    flickerAnim->setLoopCount(-1);

    // 显示或隐藏的时候，显示动画
    connect(this, &ArrangedWidget::visibleChanged, [this](bool visible){
        if (visible)
            flickerAnim->start();
        else
            flickerAnim->stop();
    });
}

// 设置剩余通知数目
void NotifyCountWidget::setCount(int count)
{
    m_pLabCount->setNum(count);
}
