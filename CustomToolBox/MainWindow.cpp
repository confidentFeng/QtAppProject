#include "MainWindow.h"
#include "ToolBox.h"
#include "Form.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 初始化主界面
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setFixedSize(362, 535);
    this->setObjectName("MainWindow");
    this->setWindowTitle(QStringLiteral("自定义ToolBox演示"));

    // 初始化ToolBox
    ToolBox *toolBox = new ToolBox;
    Form *pForm1 = new Form(nullptr, QStringList({"标签", "按钮", "编辑框", "勾选框"}));
    Form *pForm2 = new Form(nullptr, QStringList({"QStackWidget", "QTabWidget"}));
    Form *pForm3 = new Form(nullptr, QStringList({"移动", "抖动", "渐隐"}));
    Form *pForm4 = new Form(nullptr, QStringList({"进阶1", "进阶2", "进阶3"}));
    toolBox->addWidget(QStringLiteral("控件"), pForm1);
    toolBox->addWidget(QStringLiteral("页面切换"), pForm2);
    toolBox->addWidget(QStringLiteral("动画"), pForm3);
    toolBox->addWidget(QStringLiteral("进阶"), pForm4);

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addWidget(toolBox);
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);

    // 取消其他界面中所有按钮的选中状态
    connect(pForm1, &Form::sigChecked, [=]{
        pForm2->setUncheckAll();
        pForm3->setUncheckAll();
        pForm4->setUncheckAll();
    });
    connect(pForm2, &Form::sigChecked, [=]{
        pForm1->setUncheckAll();
        pForm3->setUncheckAll();
        pForm4->setUncheckAll();
    });
    connect(pForm3, &Form::sigChecked, [=]{
        pForm1->setUncheckAll();
        pForm2->setUncheckAll();
        pForm4->setUncheckAll();
    });
    connect(pForm4, &Form::sigChecked, [=]{
        pForm1->setUncheckAll();
        pForm2->setUncheckAll();
        pForm3->setUncheckAll();
    });
}

MainWindow::~MainWindow()
{

}

