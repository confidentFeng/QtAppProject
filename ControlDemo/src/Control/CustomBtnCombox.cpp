#include "CustomBtnCombox.h"

CustomBtnCombox::CustomBtnCombox(QString color, QWidget *parent)
{
    Q_UNUSED(color);
    Q_UNUSED(parent);

    // 窗口部件初始化
    pLabIcon1 = new QLabel;
    pLabText = new QLabel;
    pLabIcon2 = new QLabel;
    pLabIcon1->setStyleSheet("background:transparent;");
    pLabText->setStyleSheet("background:transparent;color:white; font-size:14px;");
    pLabIcon2->setStyleSheet("background:transparent;");
    m_pLabSpace = new QLabel;
    m_pLabSpace->setFixedSize(24, height());
    m_pLabSpace->setStyleSheet("background:transparent;");

    // 布局
    pLayoutMain = new QHBoxLayout(this);
    pLayoutMain->addSpacing(24);
    pLayoutMain->addWidget(pLabIcon1);
    pLayoutMain->addSpacing(12);
    pLayoutMain->addWidget(pLabText);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(pLabIcon2);
    pLayoutMain->addWidget(m_pLabSpace);
    pLayoutMain->addSpacing(0);
    pLayoutMain->setMargin(0);

    // 最初的样式
    this->setStyleSheet(QString("QPushButton{background:%1;border:none;}"
                        "QPushButton:hover{background:rgba(5,70,108,0.5);border:none;}"
                        "QPushButton:pressed{background:rgba(0,102,204,0.5);border:none;}").arg(color));

    // arm下自定义鼠标光标样式（arm默认系统鼠标样式比不上Windows上的好看）
    this->setCursor(QCursor(QPixmap(":/Image/Util/icon_cursorHand.png")));
}

// 鼠标移入事件
void CustomBtnCombox::enterEvent(QEvent *e)
{
    Q_UNUSED(e);

    if(m_isFold)
        this->setStyleSheet(STYLE_HOVER);
}

// 鼠标移出事件
void CustomBtnCombox::leaveEvent(QEvent *e)
{
    Q_UNUSED(e);

    if(m_isFold)
        this->setStyleSheet(STYLE_NORMAL);
}

void CustomBtnCombox::setBtnText(const QString &sText)
{
    pLabText->setText(sText);
}

void CustomBtnCombox::setLabIcon1(const QString &sImgPath)
{
    pLabIcon1->setPixmap(QPixmap(sImgPath));
}

void CustomBtnCombox::setLabIcon2(const QString &sImgPath)
{
    pLabIcon2->setPixmap(QPixmap(sImgPath));
}

void CustomBtnCombox::setBtnTextColor(const QString &sColor)
{
    pLabText->setStyleSheet(QString("background:transparent;color:%1; font-size:14px;").arg(sColor));
}

void CustomBtnCombox::setLableHide(bool isHide)
{
    if(isHide) {
        pLayoutMain->removeWidget(pLabIcon2);
        pLayoutMain->removeWidget(m_pLabSpace);
    }
}

CustomBtnComboxSw::CustomBtnComboxSw(QWidget *parent) : QPushButton(parent)
{
    // 窗口部件初始化
    pLabIcon1 = new QLabel;
    pLabText = new QLabel;
    pLabTip = new QLabel;
    m_pSwitchBtn = new CustomBtnSw;
    m_pSwitchBtn->setFixedSize(40, 20);
    m_pSwitchBtn->setButtonStyle(CustomBtnSw::ButtonStyle_CircleIn);
    m_pSwitchBtn->setChecked(false);
    pLabIcon1->setStyleSheet("background:transparent;");
    pLabText->setStyleSheet("background:transparent;color:white; font-size:14px;");
    pLabTip->setPixmap(QPixmap(":/Image/Control/icon_tip.png"));
    pLabTip->installEventFilter(this);
    pLabTip->hide();

    // 布局
    QHBoxLayout *pLayoutMain = new QHBoxLayout(this);
    pLayoutMain->addSpacing(24);
    pLayoutMain->addWidget(pLabIcon1);
    pLayoutMain->addSpacing(12);
    pLayoutMain->addWidget(pLabText);
    pLayoutMain->addSpacing(2);
    pLayoutMain->addWidget(pLabTip);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pSwitchBtn);
    pLayoutMain->addSpacing(4);
    pLayoutMain->setMargin(0);

    // 最初的样式
    this->setStyleSheet("QPushButton{background:rgba(20,45,86,0.5);border:none;}"
                        "QPushButton:hover{background:rgba(5,70,108,0.5);border:none;}"
                        "QPushButton:pressed{background:rgba(0,102,204,0.5);border:none;}");

    // arm下自定义鼠标光标样式（arm默认系统鼠标样式比不上Windows上的好看）
    this->setCursor(QCursor(QPixmap(":/Image/Util/icon_cursorHand.png")));

    connect(m_pSwitchBtn, &CustomBtnSw::checkedChanged, [=](bool checked){
        emit switchStateChanged(checked);
    });

    connect(this, &CustomBtnComboxSw::clicked, [=]{
        m_pSwitchBtn->setChecked(!m_pSwitchBtn->getChecked());
    });
}

void CustomBtnComboxSw::setBtnText(const QString &sText){
    pLabText->setText(sText);
}

void CustomBtnComboxSw::setLabIcon1(const QString &sImgPath){
    pLabIcon1->setPixmap(QPixmap(sImgPath));
}

void CustomBtnComboxSw::setBtnTextColor(const QString &sColor){
    pLabText->setStyleSheet(QString("background:transparent;color:%1; font-size:14px;").arg(sColor));
}

void CustomBtnComboxSw::setSwitchState(bool state)
{
    m_pSwitchBtn->setChecked(state);
}

bool CustomBtnComboxSw::switchState()
{
    return m_pSwitchBtn->getChecked();
}

void CustomBtnComboxSw::setTipShow(bool isShow)
{
    pLabTip->setVisible(isShow);
}

void CustomBtnComboxSw::enterEvent(QEvent *e){
    Q_UNUSED(e);

    if(m_isFold)
        this->setStyleSheet(STYLE_HOVER);
}

void CustomBtnComboxSw::leaveEvent(QEvent *e){
    Q_UNUSED(e);

    if(m_isFold)
        this->setStyleSheet(STYLE_NORMAL);
}

// 事件过滤器
bool CustomBtnComboxSw::eventFilter(QObject *obj, QEvent *event)
{
    // 由于设置浮点数正则表达式的编辑框的双击选中只能选中一个字符，所以要手动实现
    if(obj == pLabTip)
    {
        if(event->type() == QEvent::Enter)
        {
            int tipWidth = CustomTooltip::Instance().getWidth(tr("是否选择开启麦克风？"));
            QPoint pos = (mapToGlobal(pLabTip->pos() + QPoint(((pLabTip->width()-tipWidth)/2), pLabTip->height())) + QPoint(0, -48));
            if(pos.x() + tipWidth > 1920)
                pos.setX(1920 - tipWidth - 4);
            if(pos.x() < 0)
                pos.setX(4);
            CustomTooltip::Instance().SetToolTip(tr("是否选择开启麦克风？"), pos);
        }
        else if (event->type() == QEvent::Leave)
        {
            CustomTooltip::Instance().hideWin();
        }
    }

    return QWidget::eventFilter(obj, event);
}
