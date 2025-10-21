#include "CustomEditPasswd.h"

CustomEditPasswd::CustomEditPasswd(QWidget *parent) : QLineEdit(parent)
{
    // 默认为密码模式
    this->setEchoMode(QLineEdit::Password);

    QRegExp regx("[0-9]+$"); // 限制只能输入数字
    QValidator *validator = new QRegExpValidator(regx, this);
    this->setValidator(validator);
    this->setMaxLength(8); // 限制只能输入8位

    // 添加编辑框右侧的eye按钮
    m_pBtnEye = new QPushButton;
    m_pBtnEye->setFocusPolicy(Qt::NoFocus); // 按钮已经是edit的一部分了，不应该再能被单独聚焦，否则可能导致误触
    m_pBtnEye->setObjectName("CustomEditPasswd_BtnEye");
    m_pBtnEye->setCursor(QCursor(QPixmap(CURSOR_HAND))); // 如果不设置鼠标样式，鼠标移动到按钮上依旧显示为编辑框的鼠标样式
    m_pBtnEye->setVisible(false); // 一开始隐藏右侧的清空按钮
    m_pBtnEye->installEventFilter(this);

    // 以右对齐的方式添加QWidget
    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pBtnEye, 0, Qt::AlignRight);
    pLayout->setContentsMargins(10, 0, 10, 0); // 调整左边边距，避免选中文本时误碰及更靠近图标区域

    // 编辑框文本改变
    connect(this, &QLineEdit::textChanged, [=](const QString &text) {
        if(text.isEmpty())
            m_pBtnEye->setVisible(false);
        else
            m_pBtnEye->setVisible(true);
    });
}

bool CustomEditPasswd::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
        case QEvent::MouseButtonPress:
            this->setEchoMode(QLineEdit::Normal);
            break;
        case QEvent::MouseButtonRelease:
            this->setEchoMode(QLineEdit::Password);
            break;
        default:
            break;
    }

    return QWidget::eventFilter(watched, event);
}

// 尺寸大小变化事件
void CustomEditPasswd::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    // 获取控件变化后的控件高度，设置输入范围，避免文本遮挡按钮
    int actClearW = this->height();
    this->setTextMargins(0, 0, actClearW - m_nClearBtnOffset, 0);// 设置输入区域的范围，从edit的最左到按钮的最左(包含了按钮设置的buttonMargin)
}
