#include "CustomEditIcon.h"

CustomEditIcon::CustomEditIcon(QWidget *parent) : QLineEdit(parent)
{
    // 添加编辑框左侧图标
    m_pActionLeft = new QAction(this);
    this->addAction(m_pActionLeft, QLineEdit::LeadingPosition);

    // 添加编辑框右侧的清空按钮
    m_pBtnClear = new QPushButton;
    m_pBtnClear->setFocusPolicy(Qt::NoFocus); // 按钮已经是edit的一部分了，不应该再能被单独聚焦，否则可能导致误触
    m_pBtnClear->setObjectName("MyLineEdit_BtnClear");
    m_pBtnClear->setIcon(QIcon(":/Image/Control/btn_editClear_nor.png"));
    m_pBtnClear->setCursor(QCursor(QPixmap(":/Image/Util/icon_cursorHand.png"))); // 如果不设置鼠标样式，鼠标移动到按钮上依旧显示为编辑框的鼠标样式
    m_pBtnClear->setVisible(false); // 一开始隐藏右侧的清空按钮
    // 以右对齐的方式添加QWidget
    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pBtnClear, 0, Qt::AlignRight);
    pLayout->setContentsMargins(10, 0, 10, 0); // 调整左边边距，避免选中文本时误碰及更靠近图标区域
    connect(m_pBtnClear, &QPushButton::clicked, [=]{
        this->clear();
    });

    // 编辑框文本改变，为了实现：账号和密码编辑框都输入了文本时，登录按钮才能点击
    connect(this, &QLineEdit::textChanged, [=]{
        // 编辑框有文本，才显示清空action
        if(this->text().isEmpty())
            m_pBtnClear->setVisible(false);
        else
            m_pBtnClear->setVisible(true);
    });
}

// 设置左边图标
void CustomEditIcon::setLeftIcon(const QIcon &icon)
{
    m_pActionLeft->setIcon(icon);
}

// 设置清除文本按钮的边距偏移量
void CustomEditIcon::setClearBtnOffset(int offset)
{
    m_nClearBtnOffset = offset;
}

// 尺寸大小变化事件
void CustomEditIcon::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    // 获取控件变化后的控件高度，设置输入范围，避免文本遮挡按钮
    int actClearW = this->height();
    this->setTextMargins(0, 0, actClearW - m_nClearBtnOffset, 0);// 设置输入区域的范围，从edit的最左到按钮的最左(包含了按钮设置的buttonMargin)
}
