#include "ChatRoom.h"

MeetChatRoom::MeetChatRoom(QWidget *parent)
    : QWidget(parent)
{
    // 初始化界面
    this->setFixedSize(320, 465);

    // 初始化窗口部件
    m_pWidgetTitle = new QWidget;
    m_pLabIcon = new QLabel;
    m_pLabTtile = new QLabel;
    m_pBtnClose = new QPushButton;
    m_pTextBrowser = new QTextBrowser;
    m_pTextEdit = new QTextEdit;
    m_pBtnSend = new QPushButton;
    m_pWidgetTitle->setObjectName("ChatRoom_WidgetTitle");
    m_pLabIcon->setObjectName("ChatRoom_LabIcon");
    m_pLabTtile->setObjectName("ChatRoom_LabTtile");
    m_pBtnClose->setObjectName("ChatRoom_BtnClose");
    m_pTextBrowser->setObjectName("ChatRoom_TextBrowser");
    m_pTextEdit->setObjectName("ChatRoom_TextEdit");
    m_pBtnSend->setObjectName("ChatRoom_BtnSend");
    m_pWidgetTitle->setFixedSize(width(), 28);
    m_pTextBrowser->setFixedSize(304, 280);
    m_pTextEdit->setFixedSize(304, 108);
    m_pBtnSend->setFixedSize(60, 24);
    m_pLabTtile->setText(tr("聊天"));
    m_pTextEdit->setPlaceholderText(tr("请输入消息..."));
    m_pBtnSend->setText(tr("发送"));
    m_pLabIcon->setPixmap(QPixmap(":/icon_chat.png"));
    m_pTextEdit->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu); // 关闭右键菜单
    m_pTextBrowser->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);

    // 主窗口布局
    QHBoxLayout *pLayoutTitle = new QHBoxLayout(m_pWidgetTitle);
    pLayoutTitle->addSpacing(8);
    pLayoutTitle->addWidget(m_pLabIcon);
    pLayoutTitle->addSpacing(8);
    pLayoutTitle->addWidget(m_pLabTtile);
    pLayoutTitle->addStretch();
    pLayoutTitle->addWidget(m_pBtnClose);
    pLayoutTitle->addSpacing(8);
    pLayoutTitle->setSpacing(0);
    pLayoutTitle->setMargin(0);
    // 主窗口布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addSpacing(4);
    pLayoutMain->addWidget(m_pWidgetTitle);
    pLayoutMain->addWidget(m_pTextBrowser, 0, Qt::AlignHCenter);
    pLayoutMain->addSpacing(8);
    pLayoutMain->addWidget(m_pTextEdit, 0, Qt::AlignHCenter);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pBtnSend, 0, Qt::AlignRight);
    pLayoutMain->addStretch();
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);

    // 初始化定时器
    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(1000*60*3);
    m_pTimer->setSingleShot(true);
    connect(m_pTimer, &QTimer::timeout, [=]{
        m_isEnableTime = true;
    });

    // 关闭按钮
    connect(m_pBtnClose, &QPushButton::clicked, [=]{
        this->hide();
    });

    // 发送按钮
    connect(m_pBtnSend, &QPushButton::clicked, [=]{
        // 构造发送信息
        QString htmlHead = "<p style='line-height:4px; width:100% ; white-space: pre-wrap; %1'>";
        QString htmlTail = "</p>";
        QString currentTime = htmlHead + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + QDateTime::currentDateTime().toString("hh:mm") + htmlTail; // yyyy-MM-dd hh:mm:ss
        QString userName = "用户1";
        userName = htmlHead.arg("color:green;") + userName + htmlTail;
        QString message = htmlHead + m_pTextEdit->toHtml() + htmlTail; // 要用这个函数，便于设置字体格式

        if(m_pTextEdit->toPlainText() != "")
        {
            // 给指定用户发消息
            //sendMsg(Msg, sendLineText);

            // 本地选择是否添加时间
            if(m_isEnableTime) {
                m_pTextBrowser->append(currentTime);
                m_isEnableTime = false;
                m_pTimer->start();
            }
            // 本地添加用户名
            m_pTextBrowser->append(userName);
            // 本地添加显示消息
            m_pTextBrowser->append(message);
        }

        // 清空发送区
        m_pTextEdit->clear();
    });
}


