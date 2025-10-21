#include "CustomBtnWidget.h"

CustomBtnWidget::CustomBtnWidget(QWidget *parent) : QWidget(parent)
{
    // 初始化界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setFixedSize(STACK_WIDTH, STACK_HEIGHT);
    this->setObjectName("CustomBtnWidget");

    // Falt按钮
    m_pBtnFalt1 = new QPushButton;
    m_pBtnFalt2 = new QPushButton;
    m_pBtnFalt3 = new QPushButton;
    m_pBtnFalt4 = new QPushButton;
    m_pBtnFalt1->setFixedSize(150, 36);
    m_pBtnFalt2->setFixedSize(150, 36);
    m_pBtnFalt3->setFixedSize(150, 36);
    m_pBtnFalt4->setFixedSize(150, 36);
    m_pBtnFalt1->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    m_pBtnFalt2->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    m_pBtnFalt3->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    m_pBtnFalt4->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    FlatUI::setPushButtonQss(m_pBtnFalt1);
    FlatUI::setPushButtonQss(m_pBtnFalt2, 8, 14, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(m_pBtnFalt3, 8, 14, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
    FlatUI::setPushButtonQss(m_pBtnFalt4, 8, 14, "#E74C3C", "#FFFFFF", "#EC7064", "#FFF5E7", "#DC2D1A", "#F5A996");
    // Falt按钮分组框
    m_pGroupFalt = new QGroupBox;
    m_pGroupFalt->setFixedSize(STACK_WIDTH-160, 80);
    // Falt按钮分组框布局
    QHBoxLayout *pLayoutFaltBtn = new QHBoxLayout(m_pGroupFalt);
    pLayoutFaltBtn->addStretch();
    pLayoutFaltBtn->addWidget(m_pBtnFalt1);
    pLayoutFaltBtn->addStretch();
    pLayoutFaltBtn->addWidget(m_pBtnFalt2);
    pLayoutFaltBtn->addStretch();
    pLayoutFaltBtn->addWidget(m_pBtnFalt3);
    pLayoutFaltBtn->addStretch();
    pLayoutFaltBtn->addWidget(m_pBtnFalt4);
    pLayoutFaltBtn->addStretch();
    pLayoutFaltBtn->setSpacing(0);
    pLayoutFaltBtn->setMargin(0);

    // 开关按钮-内圆形
    pSwitchButton = new CustomBtnSw;
    pSwitchButton->setFixedSize(50, 24);
    pSwitchButton->setButtonStyle(CustomBtnSw::ButtonStyle_CircleIn);
    // 开关按钮-内圆形带文本
    pSwitchButtonText = new CustomBtnSw;
    pSwitchButtonText->setFixedSize(56, 24);
    pSwitchButtonText->setButtonStyle(CustomBtnSw::ButtonStyle_CircleIn);
    pSwitchButtonText->setText("OFF", "ON");
    // 开关按钮-内圆形带文本
    pSwitchButtonText2 = new CustomBtnSw;
    pSwitchButtonText2->setFixedSize(56, 24);
    pSwitchButtonText2->setButtonStyle(CustomBtnSw::ButtonStyle_CircleIn);
    pSwitchButtonText2->setText("关闭", "开启");
    // 开关按钮-外圆形
    pSwitchButtonOut = new CustomBtnSw;
    pSwitchButtonOut->setFixedSize(50, 24);
    pSwitchButtonOut->setButtonStyle(CustomBtnSw::ButtonStyle_CircleOut);
    pSwitchButtonOut->setRectRadius(10);
    // 开关按钮分组框
    m_pGroupSwitch = new QGroupBox;
    m_pGroupSwitch->setFixedSize(STACK_WIDTH-160, 80);
    // Falt按钮分组框布局
    QHBoxLayout *pLayoutSwitch = new QHBoxLayout(m_pGroupSwitch);
    pLayoutSwitch->addStretch();
    pLayoutSwitch->addWidget(pSwitchButton);
    pLayoutSwitch->addStretch();
    pLayoutSwitch->addWidget(pSwitchButtonText);
    pLayoutSwitch->addStretch();
    pLayoutSwitch->addWidget(pSwitchButtonText2);
    pLayoutSwitch->addStretch();
    pLayoutSwitch->addWidget(pSwitchButtonOut);
    pLayoutSwitch->addStretch();
    pLayoutSwitch->setSpacing(0);
    pLayoutSwitch->setMargin(0);

    // 图标按钮
    m_pBtnIcon1 = new CustomBtnIcon;
    m_pBtnIcon2 = new CustomBtnIcon;
    m_pBtnIcon3 = new CustomBtnIcon;
    m_pBtnIcon4 = new CustomBtnIcon;
    m_pBtnOther = new CustomBtnIcon;
    m_pBtnIcon1->setObjectName("CustomBtnWidget_BtnIcon");
    m_pBtnIcon2->setObjectName("CustomBtnWidget_BtnIcon");
    m_pBtnIcon3->setObjectName("CustomBtnWidget_BtnIcon");
    m_pBtnIcon4->setObjectName("CustomBtnWidget_BtnIcon");
    m_pBtnIcon1->setFixedSize(60, 30);
    m_pBtnIcon2->setFixedSize(60, 30);
    m_pBtnIcon3->setFixedSize(60, 30);
    m_pBtnIcon4->setFixedSize(60, 30);
    m_pBtnIcon1->m_iconNormal = ":/Image/Control/btn_download_nor.png";
    m_pBtnIcon1->m_iconHover = ":/Image/Control/btn_download_hov.png";
    m_pBtnIcon1->m_iconPressed = ":/Image/Control/btn_download_pre.png";
    m_pBtnIcon2->m_iconNormal = ":/Image/Control/btn_upload_nor.png";
    m_pBtnIcon2->m_iconHover = ":/Image/Control/btn_upload_hov.png";
    m_pBtnIcon2->m_iconPressed = ":/Image/Control/btn_upload_pre.png";
    m_pBtnIcon3->m_iconNormal = ":/Image/Control/btn_move_nor.png";
    m_pBtnIcon3->m_iconHover = ":/Image/Control/btn_move_hov.png";
    m_pBtnIcon3->m_iconPressed = ":/Image/Control/btn_move_pre.png";
    m_pBtnIcon4->m_iconNormal = ":/Image/Control/btn_remote_nor.png";
    m_pBtnIcon4->m_iconHover = ":/Image/Control/btn_remote_hov.png";
    m_pBtnIcon4->m_iconPressed = ":/Image/Control/btn_remote_pre.png";
    // 设置互斥
    m_pBtnIcon1->setCheckable(true);
    m_pBtnIcon2->setCheckable(true);
    m_pBtnIcon3->setCheckable(true);
    m_pBtnIcon4->setCheckable(true);
    m_pBtnOther->setCheckable(true);
    // 将需要互斥的按钮全部添加到QButtonGroup中
    QButtonGroup *box = new QButtonGroup;
    box->setExclusive(true); // 设置是否互斥
    box->addButton(m_pBtnIcon1);
    box->addButton(m_pBtnIcon2);
    box->addButton(m_pBtnIcon3);
    box->addButton(m_pBtnIcon4);
    box->addButton(m_pBtnOther);
    m_pBtnIcon1->setChecked(true); // 默认先选中一个按钮
    // 图标按钮分组框
    m_pGroupIcon = new QGroupBox;
    m_pGroupIcon->setFixedSize(STACK_WIDTH-160, 80);
    // 图标按钮分组框布局
    QHBoxLayout *pLayoutIcon = new QHBoxLayout(m_pGroupIcon);
    pLayoutIcon->addStretch();
    pLayoutIcon->addWidget(m_pBtnIcon1);
    pLayoutIcon->addStretch();
    pLayoutIcon->addWidget(m_pBtnIcon2);
    pLayoutIcon->addStretch();
    pLayoutIcon->addWidget(m_pBtnIcon3);
    pLayoutIcon->addStretch();
    pLayoutIcon->addWidget(m_pBtnIcon4);
    pLayoutIcon->addStretch();
    pLayoutIcon->setSpacing(0);
    pLayoutIcon->setMargin(0);

    // 初始化下方按钮子界面
    m_pWidgetBtn = new QWidget;
    m_pWidgetBtn->setFixedSize(640, 54);
    m_pWidgetBtn->setObjectName("CustomBtnWidget_WidgetBtn");
    // 图标在上方的按钮
    m_pBtnMember = new QPushButton;
    m_pBtnChat = new QPushButton;
    m_pBtnMike = new QPushButton;
    m_pBtnCamera = new QPushButton;
    m_pBtnMember->setObjectName("CustomBtnWidget_BtnMember");
    m_pBtnChat->setObjectName("CustomBtnWidget_BtnChat");
    m_pBtnMike->setObjectName("CustomBtnWidget_BtnMike");
    m_pBtnCamera->setObjectName("CustomBtnWidget_BtnCamera");
    m_pBtnMember->setFixedSize(72, 46);
    m_pBtnChat->setFixedSize(72, 46);
    m_pBtnMike->setFixedSize(40, 46);
    m_pBtnCamera->setFixedSize(44, 46);
    m_pBtnMember->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    m_pBtnChat->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    m_pBtnMike->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    m_pBtnCamera->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    m_pBtnMember->setCheckable(true);
    m_pBtnChat->setCheckable(true);
    m_pBtnMike->setCheckable(true);
    m_pBtnCamera->setCheckable(true);
    m_pBtnMike->setChecked(true);
    m_pBtnCamera->setChecked(true);
    // 图标在上方的按钮-分组框
    m_pGroupIconUp = new QGroupBox;
    m_pGroupIconUp->setFixedSize(STACK_WIDTH-160, 80);
    m_pGroupIconUp->setObjectName("CustomBtnWidget_GroupIconUp");
    // 按钮等布局
    QHBoxLayout *pHLayoutBtn = new QHBoxLayout(m_pWidgetBtn);
    pHLayoutBtn->addStretch();
    pHLayoutBtn->addWidget(m_pBtnMember);
    pHLayoutBtn->addStretch();
    pHLayoutBtn->addWidget(m_pBtnChat);
    pHLayoutBtn->addStretch();
    pHLayoutBtn->addWidget(m_pBtnMike);
    pHLayoutBtn->addStretch();
    pHLayoutBtn->addWidget(m_pBtnCamera);
    pHLayoutBtn->addStretch();
    pHLayoutBtn->setSpacing(0);
    pHLayoutBtn->setMargin(0);
    // 图标在上方的按钮-分组框布局
    QHBoxLayout *pLayoutIconUp = new QHBoxLayout(m_pGroupIconUp);
    pLayoutIconUp->addStretch();
    pLayoutIconUp->addWidget(m_pWidgetBtn);
    pLayoutIconUp->addStretch();
    pLayoutIconUp->setSpacing(0);
    pLayoutIconUp->setMargin(0);

    // 分屏按钮子界面
    m_pWidgetSplit = new QWidget;
    m_pWidgetSplit->setFixedSize(640, 54);
    m_pWidgetSplit->setObjectName("CustomBtnWidget_WidgetBtn");
    // 默认分屏按钮初始化
    m_pBtnSingle = new CustomBtnSplit;
    m_pBtnFour = new CustomBtnSplit;
    m_pBtnFive = new CustomBtnSplit;
    m_pBtnNineGrid = new CustomBtnSplit;
    // 分屏按钮分组框
    m_pGroupSplit = new QGroupBox;
    m_pGroupSplit->setFixedSize(STACK_WIDTH-160, 80);
    // 分屏按钮分组框布局
    QHBoxLayout *pLayoutSplit = new QHBoxLayout(m_pWidgetSplit);
    pLayoutSplit->addStretch();
    pLayoutSplit->addWidget(m_pBtnSingle);
    pLayoutSplit->addStretch();
    pLayoutSplit->addWidget(m_pBtnFour);
    pLayoutSplit->addStretch();
    pLayoutSplit->addWidget(m_pBtnFive);
    pLayoutSplit->addStretch();
    pLayoutSplit->addWidget(m_pBtnNineGrid);
    pLayoutSplit->addStretch();
    pLayoutSplit->setSpacing(0);
    pLayoutSplit->setMargin(0);
    // 图标在上方的按钮-分组框布局
    QHBoxLayout *pLayoutSplitGroup = new QHBoxLayout(m_pGroupSplit);
    pLayoutSplitGroup->addStretch();
    pLayoutSplitGroup->addWidget(m_pWidgetSplit);
    pLayoutSplitGroup->addStretch();
    pLayoutSplitGroup->setSpacing(0);
    pLayoutSplitGroup->setMargin(0);
    // 初始化分屏按钮
    initDefaultBnt();

    // 快捷键
    m_pBtnShortCut = new CustomBtnCombox;
    m_pBtnShortCut->setFixedSize(200, 32);
    m_pBtnShortCut->setLabIcon1(":/Image/Control/icon_shortCut.png");
    // 语言
    pBtnLanguage = new CustomBtnCombox;
    pBtnLanguage->setFixedSize(200, 32);
    pBtnLanguage->setLabIcon1(":/Image/Control/icon_language.png");
    pBtnLanguage->m_isFold = true;      //默认折叠
    pBtnLanguage->setLabIcon2(":/Image/Control/icon_arrowDown.png");
    // 虚拟键盘
    m_pKeyBoard = new CustomBtnComboxSw;
    m_pKeyBoard->setFixedSize(200, 32);
    m_pKeyBoard->setLabIcon1(":/Image/Control/icon_keyboard.png");
    // 麦克风
    m_pBtnMic = new CustomBtnComboxSw;
    m_pBtnMic->setFixedSize(200, 32);
    m_pBtnMic->setLabIcon1(":/Image/Control/icon_mike.png");
    m_pBtnMic->setTipShow(true);
    m_pBtnMic->setSwitchState(true);
    // 下拉按钮分组框
    m_pGroupCombox = new QGroupBox;
    m_pGroupCombox->setFixedSize(STACK_WIDTH-160, 80);
    // 下拉按钮分组框布局
    QHBoxLayout *pLayoutCombox = new QHBoxLayout(m_pGroupCombox);
    pLayoutCombox->addStretch();
    pLayoutCombox->addWidget(m_pBtnShortCut);
    pLayoutCombox->addStretch();
    pLayoutCombox->addWidget(pBtnLanguage);
    pLayoutCombox->addStretch();
    pLayoutCombox->addWidget(m_pKeyBoard);
    pLayoutCombox->addStretch();
    pLayoutCombox->addWidget(m_pBtnMic);
    pLayoutCombox->addStretch();
    pLayoutCombox->setSpacing(0);
    pLayoutCombox->setMargin(0);

    // 边框按钮
    m_pCustomBtnBorder = new CustomBtnBorder;
    m_pCustomBtnBorder->setFixedSize(160, 48);
    m_pCustomBtnBorder->setIconPixmap(QPixmap(":/Image/Control/btn_browse Folder_unchecked.png")); // 平时的图标图像
    m_pCustomBtnBorder->setIconPixmapChecked(QPixmap(":/Image/Control/btn_browse Folder_checked.png")); // 选中时的图标图像
    m_pCustomBtnBorder->setIconPixmapDis(QPixmap(":/Image/Control/btn_browse Folder_dis.png")); // 禁用时的图标图像
    m_pCustomBtnBorder->setIconSize(QSize(32, 32));
    m_pCustomBtnBorder->setBtnText("搜索");
    m_pCustomBtnBorder->setChecked(true);
    // 特殊按钮分组框
    m_pGroupSpecial = new QGroupBox;
    m_pGroupSpecial->setFixedSize(STACK_WIDTH-160, 80);
    // 特殊按钮分组框布局
    QHBoxLayout *pLayoutSpecial = new QHBoxLayout(m_pGroupSpecial);
    pLayoutSpecial->addStretch();
    pLayoutSpecial->addWidget(m_pCustomBtnBorder);
    pLayoutSpecial->addStretch();
    pLayoutSpecial->addStretch();
    pLayoutSpecial->setSpacing(0);
    pLayoutSpecial->setMargin(0);

    // 创建滚动显示区域幕布
    m_pWidgetScroll = new QWidget();
    m_pWidgetScroll->setObjectName("CustomBtnWidget_WidgetBack");

    // 创建布局, 用于将控件嵌入幕布中
    QVBoxLayout *pLayoutBack = new QVBoxLayout(m_pWidgetScroll);
    pLayoutBack->addSpacing(32);
    pLayoutBack->addWidget(m_pGroupFalt, 0, Qt::AlignHCenter);
    pLayoutBack->addWidget(m_pGroupSwitch, 0, Qt::AlignHCenter);
    pLayoutBack->addWidget(m_pGroupIcon, 0, Qt::AlignHCenter);
    pLayoutBack->addWidget(m_pGroupIconUp, 0, Qt::AlignHCenter);
    pLayoutBack->addWidget(m_pGroupSplit, 0, Qt::AlignHCenter);
    pLayoutBack->addWidget(m_pGroupCombox, 0, Qt::AlignHCenter);
    pLayoutBack->addWidget(m_pGroupSpecial, 0, Qt::AlignHCenter);
    pLayoutBack->addSpacing(32);
    pLayoutBack->addStretch();
    pLayoutBack->setSpacing(48);
    pLayoutBack->setMargin(0);

    // 创建滚动显示区域
    m_pScrollArea = new QScrollArea;
    m_pScrollArea->setAlignment(Qt::AlignHCenter); // 设置滚动区域位置
    m_pScrollArea->setObjectName("CustomBtnWidget_ScrollArea");
    m_pScrollArea->setFixedSize(width()-16, height()); // 16是滚动条的宽度
    m_pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pScrollArea->setWidget(m_pWidgetScroll); // 将设置好的幕布嵌入到滚动显示区域

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addWidget(m_pScrollArea); // 将滚动显示区域 添加到布局
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);

    // 语言
    connect(pBtnLanguage, &QPushButton::clicked, [=]{
        if(pBtnLanguage->m_isFold) {
            pBtnLanguage->m_isFold = false;
            pBtnLanguage->setLabIcon2(":/Image/Control/icon_arrowUp.png");
            pBtnLanguage->setStyleSheet("background:rgba(0,102,204,0.5);border:none;");
        }
        else {
            pBtnLanguage->m_isFold = true;
            pBtnLanguage->setLabIcon2(":/Image/Control/icon_arrowDown.png");
            pBtnLanguage->setStyleSheet(STYLE_NORMAL);
        }
    });

    // 麦克风开关
    connect(m_pBtnMic, &CustomBtnComboxSw::switchStateChanged, [=](bool checked){
        qDebug() << "m_pBtnMic" << checked;
    });

    // 统一设置需要被翻译的文本
    translateUI();
}

// 统一设置需要被翻译的文本
void CustomBtnWidget::translateUI()
{
    m_pBtnFalt1->setText(tr("Flat按钮"));
    m_pBtnFalt2->setText(tr("Flat按钮"));
    m_pBtnFalt3->setText(tr("Flat按钮"));
    m_pBtnFalt4->setText(tr("Flat按钮"));

    m_pBtnIcon1->setText(tr("下载"));
    m_pBtnIcon2->setText(tr("上传"));
    m_pBtnIcon3->setText(tr("移动"));
    m_pBtnIcon4->setText(tr("远程"));

    m_pBtnMember->setText(tr("成员"));
    m_pBtnChat->setText(tr("聊天"));
    m_pBtnCamera->setText(tr("摄像头"));
    m_pBtnMike->setText(tr("麦克风"));

    m_pBtnShortCut->setBtnText(tr("快捷键"));
    m_pKeyBoard->setBtnText(tr("虚拟键盘"));
    pBtnLanguage->setBtnText(tr("语言"));
    m_pBtnMic->setBtnText(tr("麦克风"));

    m_pGroupFalt->setTitle(tr("Flat按钮"));
    m_pGroupSwitch->setTitle(tr("开关按钮"));
    m_pGroupIcon->setTitle(tr("互斥图标按钮"));
    m_pGroupIconUp->setTitle(tr("上方图标按钮"));
    m_pGroupSplit->setTitle(tr("分屏按钮"));
    m_pGroupCombox->setTitle(tr("下拉开关按钮"));
    m_pGroupSpecial->setTitle(tr("特殊按钮"));
}

// 初始化分屏按钮
void CustomBtnWidget::initDefaultBnt()
{
    // 单分屏
    QVector<StGrid> vecRectSingle;
    vecRectSingle.append(StructGrid(QRect(0, 0, SPLIT_WIDTH, SPLIT_HEIGHT)));
    m_pBtnSingle->setGridVector(vecRectSingle);
    // 四分屏
    QVector<StGrid> vecRectFour;
    vecRectFour.append(StructGrid(QRect(0, 0, SPLIT_WIDTH/2, SPLIT_HEIGHT/2)));
    vecRectFour.append(StructGrid(QRect(SPLIT_WIDTH/2, 0, SPLIT_WIDTH/2, SPLIT_HEIGHT/2)));
    vecRectFour.append(StructGrid(QRect(0, SPLIT_HEIGHT/2, SPLIT_WIDTH/2, SPLIT_HEIGHT/2)));
    vecRectFour.append(StructGrid(QRect(SPLIT_WIDTH/2, SPLIT_HEIGHT/2, SPLIT_WIDTH/2, SPLIT_HEIGHT/2)));
    m_pBtnFour->setGridVector(vecRectFour);
    // 一大五小
    QVector<StGrid> vecRectFive;
    vecRectFive.append(StructGrid(QRect(0, 0, (SPLIT_WIDTH/3)*2, (SPLIT_HEIGHT/3)*2)));
    vecRectFive.append(StructGrid(QRect((SPLIT_WIDTH/3)*2, 0, SPLIT_WIDTH/3, SPLIT_HEIGHT/3)));
    vecRectFive.append(StructGrid(QRect((SPLIT_WIDTH/3)*2, (SPLIT_HEIGHT/3)*1, SPLIT_WIDTH/3, SPLIT_HEIGHT/3)));
    vecRectFive.append(StructGrid(QRect(0, (SPLIT_HEIGHT/3)*2, SPLIT_WIDTH/3, SPLIT_HEIGHT/3)));
    vecRectFive.append(StructGrid(QRect((SPLIT_WIDTH/3)*1, (SPLIT_HEIGHT/3)*2, SPLIT_WIDTH/3, SPLIT_HEIGHT/3)));
    vecRectFive.append(StructGrid(QRect((SPLIT_WIDTH/3)*2, (SPLIT_HEIGHT/3)*2, SPLIT_WIDTH/3, SPLIT_HEIGHT/3)));
    m_pBtnFive->setGridVector(vecRectFive);
    // 九宫格
    QVector<StGrid> vecRectNineGrid;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            vecRectNineGrid.append(StructGrid(QRect(j*(SPLIT_WIDTH/3), i*(SPLIT_HEIGHT/3), SPLIT_WIDTH/3, SPLIT_HEIGHT/3)));
        }
    }
    m_pBtnNineGrid->setGridVector(vecRectNineGrid);

    // 初始化默认分屏按钮
    m_pBtnSingle->setSplitMode(SplitSingle);
    m_pBtnFour->setSplitMode(SplitFour);
    m_pBtnFive->setSplitMode(SplitOneBigFiveSmall);
    m_pBtnNineGrid->setSplitMode(SplitNineGrid);
    // 将分屏按钮存放到容器中，方便通过"分屏模式"映射到相应的"分屏按钮"
    m_vecSplitBtn.append(m_pBtnSingle);
    m_vecSplitBtn.append(m_pBtnFour);
    m_vecSplitBtn.append(m_pBtnFive);
    m_vecSplitBtn.append(m_pBtnNineGrid);

    // 遍历设置信号槽，实现互斥选中功能
    for(auto item : m_vecSplitBtn) {
        connect(item, &CustomBtnSplit::sigChecked, [=](EnumSplitMode splitMode){
            for(auto item : m_vecSplitBtn) {
                if(splitMode != item->getSplitMode())
                    item->setChecked(false);
            }
        });
    }
}
