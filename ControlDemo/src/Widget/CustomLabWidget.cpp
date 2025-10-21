#include "CustomLabWidget.h"

CustomLabWidget::CustomLabWidget(QWidget *parent) : QWidget(parent)
{
    // 初始化界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setFixedSize(STACK_WIDTH, STACK_HEIGHT);
    this->setObjectName("CustomBtnWidget");

    // 图标标签
    m_pLabIcon1 = new QLabel;
    m_pLabIcon2 = new QLabel;
    m_pLabIcon3 = new QLabel;
    m_pLabIcon4 = new QLabel;
    m_pLabIcon1->setPixmap(QPixmap(":/Image/Widget/phone.png"));
    m_pLabIcon2->setPixmap(QPixmap(":/Image/Widget/umbrella.png"));
    m_pLabIcon3->setPixmap(QPixmap(":/Image/Widget/modular.png"));
    m_pLabIcon4->setPixmap(QPixmap(":/Image/Widget/money.png"));
    // 分组框
    m_pGroupIcon = new QGroupBox;
    m_pGroupIcon->setFixedSize(STACK_WIDTH-160, 140);
    m_pGroupIcon->setTitle(tr("图标标签"));
    // 布局
    QHBoxLayout *pLayoutIcon = new QHBoxLayout(m_pGroupIcon);
    pLayoutIcon->addStretch();
    pLayoutIcon->addWidget(m_pLabIcon1);
    pLayoutIcon->addStretch();
    pLayoutIcon->addWidget(m_pLabIcon2);
    pLayoutIcon->addStretch();
    pLayoutIcon->addWidget(m_pLabIcon3);
    pLayoutIcon->addStretch();
    pLayoutIcon->addWidget(m_pLabIcon4);
    pLayoutIcon->addStretch();
    pLayoutIcon->setSpacing(0);
    pLayoutIcon->setMargin(0);

    /********** 省略文本 ***********/
    QString strText = "举头望明月，低头思故乡";
    // 省略标签1
    m_pLabOmit1 = new QLabel;
    m_pLabOmit1->setObjectName("CustomBtnWidget_LabOmit");
    m_pLabOmit1->setFixedSize(120, 28);
    // 省略处理1
    QString strElidedText = m_pLabOmit1->fontMetrics().elidedText(strText, Qt::ElideRight, m_pLabOmit1->width()-16, Qt::TextShowMnemonic);
    m_pLabOmit1->setText(strElidedText);
    // 省略标签2
    m_pLabOmit2 = new QLabel;
    m_pLabOmit2->setObjectName("CustomBtnWidget_LabOmit");
    m_pLabOmit2->setFixedSize(120, 28);
    // 省略处理2
    QString strElidedText2 = m_pLabOmit2->fontMetrics().elidedText(strText, Qt::ElideLeft, m_pLabOmit2->width()-16, Qt::TextShowMnemonic);
    m_pLabOmit2->setText(strElidedText2);
    // 省略标签3
    m_pLabOmit3 = new QLabel;
    m_pLabOmit3->setObjectName("CustomBtnWidget_LabOmit");
    m_pLabOmit3->setFixedSize(120, 28);
    // 省略处理3
    QString strElidedText3 = m_pLabOmit3->fontMetrics().elidedText(strText, Qt::ElideMiddle, m_pLabOmit3->width()-16, Qt::TextShowMnemonic);
    m_pLabOmit3->setText(strElidedText3);

    // 滚动显示标签
    m_pCustomLabScroll = new CustomLabScroll;
    m_pCustomLabScroll->setText(strText);
    m_pCustomLabScroll->setFixedSize(150, 28);

    // 分组框
    m_pGroupOmit = new QGroupBox;
    m_pGroupOmit->setFixedSize(STACK_WIDTH-160, 140);
    m_pGroupOmit->setTitle(tr("省略与滚动显示标签"));
    // 布局
    QHBoxLayout *pLayoutOmit = new QHBoxLayout(m_pGroupOmit);
    pLayoutOmit->addStretch();
    pLayoutOmit->addWidget(m_pLabOmit1);
    pLayoutOmit->addStretch();
    pLayoutOmit->addWidget(m_pLabOmit2);
    pLayoutOmit->addStretch();
    pLayoutOmit->addWidget(m_pLabOmit3);
    pLayoutOmit->addStretch();
    pLayoutOmit->addWidget(m_pCustomLabScroll);
    pLayoutOmit->addStretch();
    pLayoutOmit->setSpacing(0);
    pLayoutOmit->setMargin(0);

    // gif标签
    m_pLabGif = new QLabel;
    QMovie *pMovie = new QMovie(":/Image/Widget/icon-loading.gif");
    m_pLabGif->setMovie(pMovie);
    m_pLabGif->setFixedSize(31, 31);
    m_pLabGif->setScaledContents(true);
    pMovie->start(); // 播放加载的动画
    // 自定义加载标签
    m_pCustomLabLoad = new CustomLabLoad;
    m_pCustomLabLoad->setImageCount(":/Image/Widget/loading", 8);
    m_pCustomLabLoad->setInterval(300);
    // 分组框
    m_pGroupGif = new QGroupBox;
    m_pGroupGif->setFixedSize(STACK_WIDTH-160, 140);
    m_pGroupGif->setTitle(tr("Gif标签"));
    // 布局
    QHBoxLayout *pLayoutGif= new QHBoxLayout(m_pGroupGif);
    pLayoutGif->addStretch();
    pLayoutGif->addWidget(m_pLabGif);
    pLayoutGif->addStretch();
    pLayoutGif->addWidget(m_pCustomLabLoad);
    pLayoutGif->addStretch();
    pLayoutGif->setSpacing(0);
    pLayoutGif->setMargin(0);

    // 富文本标签
    m_pLabRich = new QLabel;
    m_pLabRich->setText("<p style=\"color:#fd839a;font-size:16px;\">世界<b style=\"color:green;font-size:22px;\">和平</b></p>");
    // 超链接标签
    m_pLabUrl = new QLabel;
    m_pLabUrl->setText("<a style='color:#fd839a; font-size:16px;' href=\"https://www.baidu.com\">百度一下</a>"); // 设置超链接文本内容
    m_pLabUrl->setOpenExternalLinks(true); // 开启点击自动跳转到超链接地址，默认为false
    //鼠标点击超链接事件:
    //void linkActivated(const QString &link)
    //鼠标放到超链接上事件
    //void linkHovered(const QString &link)
    // 分组框
    m_pGroupHtml = new QGroupBox;
    m_pGroupHtml->setFixedSize(STACK_WIDTH-160, 140);
    m_pGroupHtml->setTitle(tr("富文本与超链接标签"));
    // 布局
    QHBoxLayout *pLayoutHtml = new QHBoxLayout(m_pGroupHtml);
    pLayoutHtml->addStretch();
    pLayoutHtml->addWidget(m_pLabRich);
    pLayoutHtml->addStretch();
    pLayoutHtml->addWidget(m_pLabUrl);
    pLayoutHtml->addStretch();
    pLayoutHtml->setSpacing(0);
    pLayoutHtml->setMargin(0);

    // 自定义定时隐藏提示标签
    m_pCustomLabTip = new CustomLabTip(this);
    m_pCustomLabTip->hide();

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupIcon, 0, Qt::AlignHCenter);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupOmit, 0, Qt::AlignHCenter);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupGif, 0, Qt::AlignHCenter);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupHtml, 0, Qt::AlignHCenter);
    pLayoutMain->addStretch();
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);
}

void CustomLabWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_pCustomLabTip->setTextPopup("自定义定时隐藏提示标签", 16, 1);
    m_pCustomLabTip->move((this->width()-m_pCustomLabTip->width())/2, (this->height()-m_pCustomLabTip->height())/2 + 90);
    m_pCustomLabTip->show();
}
