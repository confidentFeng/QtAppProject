#include "StandardTitleBar.h"

StandardTitleBar::StandardTitleBar(QWidget *parent) : QWidget(parent)
{
    // 初始化界面
    this->setFixedHeight(36);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setProperty("StandardTitleBar", true);
    this->setObjectName("StandardTitleBar");

    // 图标标签
    m_pLabIcon = new QLabel(this);
    m_pLabIcon->setFixedSize(20, 20);
    m_pLabIcon->setScaledContents(true);
    // 标题标签
    m_pLabTitle = new QLabel(this);

    // 最小化按钮
    m_pBtnMin = new QPushButton(this);
    m_pBtnMin->setFixedSize(30, 30);
    m_pBtnMin->setObjectName("StandardTitleBar_BtnMin");
    m_pBtnMin->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    // 最大化按钮
    m_pBtnMax = new QPushButton(this);
    m_pBtnMax->setFixedSize(30, 30);
    m_pBtnMax->setObjectName("StandardTitleBar_BtnMax");
    m_pBtnMax->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    // 关闭按钮
    m_pBtnClose = new QPushButton(this);
    m_pBtnClose->setFixedSize(30, 30);
    m_pBtnClose->setObjectName("StandardTitleBar_BtnClose");
    m_pBtnClose->setCursor(QCursor(QPixmap(CURSOR_HAND)));

    // 主布局
    QHBoxLayout* pLayoutMain = new QHBoxLayout(this);
    pLayoutMain->addWidget(m_pLabIcon);
    pLayoutMain->addSpacing(8);
    pLayoutMain->addWidget(m_pLabTitle);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pBtnMin);
    pLayoutMain->addWidget(m_pBtnMax);
    pLayoutMain->addWidget(m_pBtnClose);
    pLayoutMain->setSpacing(0);
    pLayoutMain->setContentsMargins(8, 0, 8, 0);

    // 信号槽连接
    connect(m_pBtnMin, &QPushButton::clicked, this, &StandardTitleBar::onClicked);
    connect(m_pBtnMax, &QPushButton::clicked, this, &StandardTitleBar::onClicked);
    connect(m_pBtnClose, &QPushButton::clicked, this, &StandardTitleBar::onClicked);
}

// 设置标题栏标题
void StandardTitleBar::setWindowTitle(const QString &title)
{
    m_pLabTitle->setAlignment(Qt::AlignCenter);
    m_pLabTitle->setText(title);
}

// 设置标题栏的图标
void StandardTitleBar::SetTitleBarIcon(const QString &iconPath)
{
    QPixmap map(iconPath);
    m_pLabIcon->setPixmap(map);
}

// 鼠标双击事件处理函数
void StandardTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    m_pBtnMax->click();
}

// 鼠标按下事件处理函数
void StandardTitleBar::mousePressEvent(QMouseEvent *event)
{
    // 鼠标左键按下事件
    if (event->button() == Qt::LeftButton)
    {
        // 记录鼠标左键状态
        m_leftButtonPressed = true;
        // 记录鼠标在屏幕中的位置
        m_pointStart = event->globalPos();
    }
}

// 鼠标移动事件处理函数
void StandardTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    // 持续按住才做对应事件
    if(m_leftButtonPressed)
    {
        // 将父窗体移动到父窗体原来的位置加上鼠标移动的位置：event->globalPos()-m_start
        parentWidget()->move(parentWidget()->geometry().topLeft() +
                             event->globalPos() - m_pointStart);
        // 将鼠标在屏幕中的位置替换为新的位置
        m_pointStart = event->globalPos();
    }

}

// 鼠标释放事件处理函数
void StandardTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    // 鼠标左键释放
    if (event->button() == Qt::LeftButton)
    {
        // 记录鼠标状态
        m_leftButtonPressed = false;
    }
}

// 事件过滤处理器
bool StandardTitleBar::eventFilter(QObject *obj, QEvent *event)
{
    // 设置标题
    if(event->type() == QEvent::WindowTitleChange)
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            m_pLabTitle->setText(pWidget->windowTitle());
            return true;
        }
    }
    // 设置图标
    else if(event->type() == QEvent::WindowIconChange)
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            m_pLabIcon->setPixmap(icon.pixmap(m_pLabIcon->size()));
            return true;
        }
    }
    // 窗口状态变化、窗口大小变化
    else if(event->type() == QEvent::WindowStateChange || event->type() == QEvent::Resize) {
        updateMaximize();
        return true;
    }

    return QWidget::eventFilter(obj, event);
}

// 最大化/还原
void StandardTitleBar::updateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            m_pBtnMax->setToolTip(tr("Restore"));
            m_pBtnMax->setProperty("maximizeProperty", "restore");
        }
        else
        {
            m_pBtnMax->setProperty("maximizeProperty", "maximize");
            m_pBtnMax->setToolTip(tr("Maximize"));
        }

        m_pBtnMax->setStyle(QApplication::style());
    }
}

// 最小化、最大化/还原、关闭按钮点击时响应的槽函数
void StandardTitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pBtnMin)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_pBtnMax)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == m_pBtnClose)
        {
            pWindow->close();
        }
    }
}
