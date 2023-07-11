#include "WifiListItem.h"

WifiListItem::WifiListItem(QWidget *parent) : QWidget(parent)
{
    // 初始化界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setFixedSize(WIFI_LIST_WIDTH, WIFI_ITEM_HEIGHT);
    //this->setFocusPolicy(Qt::StrongFocus); // 要注释掉，否则点击wifi按钮时，隐藏wifi按钮后，界面丢失焦点，焦点会自动跳到下一个WifiListItem
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("WifiListItem");

    // 图标标签
    m_pLabIcon = new QLabel;
    m_pLabIcon->setPixmap(QPixmap(":/Image/Wifi/icon_wifi.png"));
    // 名称标签
    m_pLabName = new QLabel;
    m_pLabName->setObjectName("WifiListItem_LabName");

    // 勾选框
    m_pCheckBox = new QCheckBox;
    m_pCheckBox->setObjectName("WifiListItem_CheckBox");
    m_pCheckBox->setText(tr("自动连接"));
    m_pCheckBox->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    // wifi按钮
    m_pBtnWifi = new QPushButton;
    m_pBtnWifi->setObjectName("WifiListItem_BtnWifi");
    m_pBtnWifi->setFixedSize(150, 36);
    m_pBtnWifi->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    // 勾选框Widget
    m_pWidgetCheck = new QWidget;
    m_pWidgetCheck->setFixedHeight(WIFI_ITEM_HEIGHT*2);
    // 勾选框布局
    QVBoxLayout *pLayoutCheck = new QVBoxLayout(m_pWidgetCheck);
    pLayoutCheck->addWidget(m_pCheckBox);
    pLayoutCheck->addStretch();
    pLayoutCheck->addWidget(m_pBtnWifi);
    pLayoutCheck->addSpacing(12);
    pLayoutCheck->setSpacing(0);
    pLayoutCheck->setMargin(0);

    // 编辑框提示文本标签
    m_pLabEditTip = new QLabel;
    m_pLabEditTip->setObjectName("WifiListItem_EditTip");
    m_pLabEditTip->setText(tr("输入网络安全秘钥"));
    // wifi密码编辑框
    m_pEditPasswd = new CustomEditPasswd;
    m_pEditPasswd->setFixedSize(300, 32);
    FlatUI::setLineEditQss(m_pEditPasswd, 0, 14, "#000000", 2, "#cfae80", "#cc8729");
    // 错误提示文本标签
    m_pLabErrorTip = new QLabel;
    m_pLabErrorTip->setObjectName("WifiListItem_LabErrorTip");
    m_pLabErrorTip->hide();
    // 下一步按钮
    m_pBtnNext = new QPushButton;
    m_pBtnNext->setText(tr("下一步"));
    m_pBtnNext->setObjectName("WifiListItem_BtnWifi");
    m_pBtnNext->setFixedSize(144, 32);
    m_pBtnNext->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    m_pBtnNext->setEnabled(false);
    // 取消按钮
    m_pBtnCancel = new QPushButton;
    m_pBtnCancel->setText(tr("取消"));
    m_pBtnCancel->setObjectName("WifiListItem_BtnWifi");
    m_pBtnCancel->setFixedSize(144, 32);
    m_pBtnCancel->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    // 编辑框Widget
    m_pWidgetEdit = new QWidget;
    m_pWidgetEdit->setFixedHeight(WIFI_ITEM_HEIGHT*2+16);
    // 下一步按钮布局
    QHBoxLayout *pLayoutBtnNext = new QHBoxLayout;
    pLayoutBtnNext->addWidget(m_pBtnNext);
    pLayoutBtnNext->addSpacing(4);
    pLayoutBtnNext->addWidget(m_pBtnCancel);
    pLayoutBtnNext->addStretch();
    pLayoutBtnNext->setSpacing(0);
    pLayoutBtnNext->setMargin(0);
    // 编辑框布局
    QVBoxLayout* pLayoutEdit = new QVBoxLayout(m_pWidgetEdit);
    pLayoutEdit->addWidget(m_pLabEditTip);
    pLayoutEdit->addSpacing(4);
    pLayoutEdit->addWidget(m_pEditPasswd);
    pLayoutEdit->addSpacing(4);
    pLayoutEdit->addWidget(m_pLabErrorTip);
    pLayoutEdit->addStretch();
    pLayoutEdit->addLayout(pLayoutBtnNext);
    pLayoutEdit->addStretch();
    pLayoutEdit->setSpacing(0);
    pLayoutEdit->setMargin(0);

    // 加载界面
    m_pLoadingWidget = new LoadingWidget;
    m_pLoadingWidget->setObjectName("LoadingWidget");
    m_pLoadingWidget->setStyleSheet("QWidget#LoadingWidget{background: transparent;}");
    m_pLoadingWidget->setProperty("canMove", false);
    m_pLoadingWidget->setFixedSize(width(), 30);
    m_pLoadingWidget->setPixmapPath(":/Image/Widget/loading", 8);
    // 验证标签
    m_pLabVerify = new QLabel;
    m_pLabVerify->setObjectName("WifiListItem_EditTip");
    m_pLabVerify->setText(tr("正在验证并连接"));
    // 连接取消按钮
    m_pBtnConCancel = new QPushButton;
    m_pBtnConCancel->setText(tr("取消"));
    m_pBtnConCancel->setObjectName("WifiListItem_BtnWifi");
    m_pBtnConCancel->setFixedSize(144, 32);
    m_pBtnConCancel->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    // 连接中Widget
    m_pWidgetConnecting = new QWidget;
    m_pWidgetConnecting->setFixedHeight(WIFI_ITEM_HEIGHT*2+16);
    // 连接中布局
    QVBoxLayout* pLayoutCon = new QVBoxLayout(m_pWidgetConnecting);
    pLayoutCon->addStretch();
    pLayoutCon->addWidget(m_pLoadingWidget, 0, Qt::AlignHCenter);
    pLayoutCon->addStretch();
    pLayoutCon->addWidget(m_pLabVerify);
    pLayoutCon->addStretch();
    pLayoutCon->addWidget(m_pBtnConCancel, 0, Qt::AlignRight);
    pLayoutCon->addStretch();
    pLayoutCon->setSpacing(0);
    pLayoutCon->setMargin(0);

    // 属性按钮
    m_pBtnLProperty = new QPushButton;
    m_pBtnLProperty->setText(tr("属性"));
    m_pBtnLProperty->setObjectName("WifiListItem_BtnLProperty");
    m_pBtnLProperty->setFixedWidth(28);
    m_pBtnLProperty->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    // 断开连接按钮
    m_pBtnDisconect = new QPushButton;
    m_pBtnDisconect->setText(tr("断开连接"));
    m_pBtnDisconect->setObjectName("WifiListItem_BtnWifi");
    m_pBtnDisconect->setFixedSize(144, 32);
    m_pBtnDisconect->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    // 已连接Widget
    m_pWidgetConnected = new QWidget;
    m_pWidgetConnected->setFixedHeight(WIFI_ITEM_HEIGHT*2+16);
    // 已连接布局
    QVBoxLayout* pLayoutConnected = new QVBoxLayout(m_pWidgetConnected);
    pLayoutConnected->addStretch();
    pLayoutConnected->addWidget(m_pBtnLProperty);
    pLayoutConnected->addStretch();
    pLayoutConnected->addWidget(m_pBtnDisconect, 0, Qt::AlignRight);
    pLayoutConnected->addStretch();
    pLayoutConnected->setSpacing(0);
    pLayoutConnected->setMargin(0);

    // 右侧布局
    QVBoxLayout* pLayoutRight = new QVBoxLayout;
    pLayoutRight->addSpacing(8);
    pLayoutRight->addWidget(m_pLabName);
    pLayoutRight->addStretch();
    pLayoutRight->addWidget(m_pWidgetCheck);
    pLayoutRight->addWidget(m_pWidgetEdit);
    pLayoutRight->addWidget(m_pWidgetConnecting);
    pLayoutRight->addWidget(m_pWidgetConnected);
    pLayoutRight->setSpacing(0);
    pLayoutRight->setMargin(0);
    // 主布局
    QHBoxLayout* pLayoutMain = new QHBoxLayout(this);
    pLayoutMain->addSpacing(4);
    pLayoutMain->addWidget(m_pLabIcon, 0, Qt::AlignTop);
    pLayoutMain->addSpacing(4);
    pLayoutMain->addLayout(pLayoutRight);
    pLayoutMain->addStretch();
    pLayoutMain->setSpacing(0);
    pLayoutMain->setContentsMargins(0, 0, 28, 0);

    // 默认为未选中状态
    this->setState(Unchecked);

    // 初始化信号槽
    initSigSlot();
}

// 设置状态
void WifiListItem::setState(WifiState wifiState)
{
    //m_wifiState = Checked;

    switch (wifiState) {
        case Unchecked:
        m_pWidgetCheck->hide();
        m_pWidgetEdit->hide();
        m_pWidgetConnecting->hide();
        m_pWidgetConnected->hide();
        this->setFixedSize(width(), WIFI_ITEM_HEIGHT);
        break;

        case Checked:
        m_pWidgetCheck->show();
        m_pWidgetEdit->hide();
        m_pWidgetConnecting->hide();
        m_pWidgetConnected->hide();
        m_pBtnWifi->setText(tr("连接"));
        this->setFixedSize(width(), WIFI_ITEM_HEIGHT*3);
        break;

        case Edit:
        m_pWidgetCheck->hide();
        m_pWidgetEdit->show();
        m_pWidgetConnecting->hide();
        m_pWidgetConnected->hide();
        this->setFixedSize(width(), WIFI_ITEM_HEIGHT*3);
        // 保存当前状态
        m_wifiState = wifiState;
        break;

        case Connecting:
        m_pWidgetCheck->hide();
        m_pWidgetEdit->hide();
        m_pWidgetConnecting->show();
        m_pWidgetConnected->hide();
        this->setFixedSize(width(), WIFI_ITEM_HEIGHT*3);
        break;

        case Connected:
        m_pWidgetCheck->hide();
        m_pWidgetEdit->hide();
        m_pWidgetConnecting->hide();
        m_pWidgetConnected->show();
        this->setFixedSize(width(), WIFI_ITEM_HEIGHT*3);
        // 保存当前状态
        m_wifiState = wifiState;
        break;

        default:
        break;
    }
}

// 获取状态
WifiState WifiListItem::getState()
{
    return m_wifiState;
}

// 设置wifi名称
void WifiListItem::setWifiName(const QString &name)
{
    m_pLabName->setText(name);
}

// 初始化信号槽
void WifiListItem::initSigSlot()
{
    // 编辑框
    connect(m_pEditPasswd, &QLineEdit::textChanged, [=](const QString &text) {
        if(text.isEmpty())
            m_pBtnNext->setEnabled(false);
        else
            m_pBtnNext->setEnabled(true);
    });

    // wifi按钮
    connect(m_pBtnWifi, &QPushButton::clicked, [=]{
        // 设置为编辑状态
        this->setState(Edit);
    });

    // 下一步按钮
    connect(m_pBtnNext, &QPushButton::clicked, [=]{
        // 1. 创建wifi配置文件
        QString strWifiName = m_pLabName->text();
        XmlHelper::Get()->WriteXml(strWifiName, m_pEditPasswd->text());
        // 2. 添加wifi配置文件
        QString strReturn = AppCommon::Get().ExecuteCmd(QString("netsh wlan add profile filename=%1/%2.xml")\
            .arg(QApplication::applicationDirPath()).arg(strWifiName));
        if (strReturn.contains("已将配置文件"))
        {
            // 密码正确，但未连接成功，则设置为连接中状态
            this->setState(Connecting);
            // 延时1.5秒，以显示加载状态
            AppCommon::Get().sleepEvent(1500);

            // 连接wifi
            QString strConReturn = AppCommon::Get().ExecuteCmd(QString("netsh wlan connect name=%1").arg(strWifiName));
            if(strConReturn.contains("已成功完成连接请求")) {
                // 连接成功，则设置为连接中状态
                this->setState(Connected);
            }
            else {
                // 密码错误，未连接成功，则设置为编辑状态
                this->setState(Edit);

                m_pLabErrorTip->setText(tr("网络安全秘钥不正确。请再试一次。"));
                m_pLabErrorTip->show(); // 错误提示
            }
        }
        else if (strReturn.contains("配置文件格式错误"))
        {
            m_pLabErrorTip->setText(tr("网络安全秘钥不正确。请再试一次。"));
            m_pLabErrorTip->show(); // 错误提示
        }

        // 不管添加wifi配置文件是否成功，都删除相应配置文件
        QString fileName = QApplication::applicationDirPath() + "/" + strWifiName + ".xml";
        QFile fileTemp(fileName);
        fileTemp.remove();
    });

    // 取消按钮
    connect(m_pBtnCancel, &QPushButton::clicked, [=]{
        m_pEditPasswd->clear();
        this->setState(Checked);
    });

    // 连接取消按钮
    connect(m_pBtnConCancel, &QPushButton::clicked, [=]{
        m_pEditPasswd->clear();
        this->setState(Checked);
    });

    // 断开连接按钮
    connect(m_pBtnDisconect, &QPushButton::clicked, [=]{
        // 连接wifi
        QString strReturn = AppCommon::Get().ExecuteCmd("netsh wlan disconnect");
        if (strReturn.contains("已成功完成接口“WLAN”的断开连接请求。"))
        {
            m_pEditPasswd->clear();
            this->setState(Checked);
        }
    });
}
