#ifndef PEACHWIDGET_H
#define PEACHWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QStackedWidget>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include "src/MessageBox/mymessagebox.h"
#include "src/Util/AppInit.h"
#include "src/Widget/ControlWidget.h"
#include "src/Widget/CarouselWidget.h"
#include "src/Widget/WifiListWidget.h"
#include "src/SplitScreen/SplitScreenWidget.h"
#include "src/SplitScreen/SplitScrCustomWidget.h"
#include "src/Widget/LoadingWidget.h"
#include "src/Widget/MaskWidget.h"
#include "src/Widget/widget.h"
#include "src/Widget/FlatUiWidget.h"
#include "src/Util/AppData.h"

class PeachWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PeachWidget(QWidget *parent = nullptr);
    void translateUI(); // 统一设置需要被翻译的文本

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void sigShowLogin(); // 显示登录界面

private slots:
    void changeMboxReturn(int num);

private:
    void initSigSlot(); // 初始化信号槽连接
    void initTray(); // 初始化托盘
    void littleShow(); // 最小化显示函数

    QWidget *m_pBackWidget; // 背景界面
    QWidget *m_pWidgetLeft; // 左侧子界面

    QLabel *m_pLabLogo;
    QLabel *m_pLabTitle;
    QPushButton *m_pBtnSet;
    QPushButton *m_pBtnHomePage;

    QLabel *m_pLabService;
    QToolButton *m_pBtnSplitScr; // 分屏按钮
    QToolButton *m_pBtnLoad;
    QToolButton *m_pBtnMask;
    QToolButton *m_pBtn4;
    QToolButton *m_pBtn5;
    QToolButton *m_pBtn6;

    QPushButton *m_pBtnLittleShow;
    QPushButton *m_pBtnHome;
    QPushButton *m_pBtnLogout;

    QPushButton *m_pBtnStack1;
    QPushButton *m_pBtnStack2;
    QPushButton *m_pBtnStack3;
    QPushButton *m_pBtnStack4;
    SplitScreenWidget *m_pSplitScreenWidget;
    SplitScrCustomWidget *m_pSplitScrCustomWidget;

    QStackedWidget *m_pStackedWidget;
    QWidget *m_pWidgetRight;

    MyMessageBox *m_pMsgBox;
    BubbleTipsWidget *m_pBubbleTip; // 冒泡提示框


    Widget *m_pWidget;


    // 自定义窗口通信参数
    int mbox_return;

    // 最小化到托盘
    QSystemTrayIcon *m_pTrayIcon;
    QMenu *m_pTrayIconMenu;
    // 窗口管理动作
    QAction *returnNormal;
    QAction *quitAction;
};

#endif // PEACHWIDGET_H
