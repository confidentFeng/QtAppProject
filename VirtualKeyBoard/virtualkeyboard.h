#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H
/*
使用说明： 使用Qwidget实现QT键盘，已经实现的功能：中英文切换、中文联想、中英文基础符号、自动弹出虚拟键盘
本工程下有一个Resources文件夹，下面有一个已经制作好的汉字数据库，需要将其放到可执行文件目录下才可正常使用汉字功能
所有样式功能均在资源文件中的QSS中实现，包括键盘背景图片的切换

如何实现中文联想：使用数据库的模糊搜索方式，实现中文联想，并自己制作汉字数据库。

作者：seejv
最后修改时间：2019-03-05

在QT版本比较低（例如5以下）的情况下中文会乱码，QT5.12不会乱码

*/
#include <QWidget>
#include <QMap>

class QPushButton;
class QSqlDatabase;
class QLineEdit;
class MyVirtualKeyBoard_qBtn;
namespace Ui {
class VirtualKeyBoard;
}




class VirtualKeyBoard : public QWidget
{
    Q_OBJECT
public:
#define ARG(InputObject) InputObject
    ~VirtualKeyBoard()override;

  static VirtualKeyBoard *getKeyboard();//变为静态后使用POP有缺陷（setAutoHide）
    explicit VirtualKeyBoard(QWidget *parent = nullptr);

    //使用说明，要求输入控件必须是自定义的
    //setTextSlot(QString)  用于更新输入控件内容
    //curTextSignal(QString)  用于获取当前文本控件的内容
    void setAutoShow(QObject* input_widget);//eg.  setAutoShow(new myLineEdit(this));//控件必须是自定义的
    void setAutoHide(bool autoHide);//是否设置为Popup模式，默认有false，Popup有些地方有些问题，没去弄



protected:
    void showEvent(QShowEvent *event)override;
    void hideEvent(QHideEvent *event)override;

private:
    Ui::VirtualKeyBoard *ui;
    static VirtualKeyBoard* keyboard_;
private:

    void init();
    void init1();//添加UI中的变量及信号与槽
    void init2();//布局、数据、等只需要初始化一次的

    QMap<int, QStringList> getChineseListMap(const QString &cur_text);//获取汉字列表，重要-----------------------------------------
    void clearBuffer();//清除拼音、等缓存
    void switchLetterStatus();//切换大小写
    QSqlDatabase* db_=nullptr;
    int cur_py_page_=-1;
    QString last_py_{};//上一次保存的可寻找到汉字的拼音组合
    QString cur_py_text_{};
    QString last_py_text_{};//用于确定退格按钮
//    QLineEdit* out_side_le_=nullptr;
    QString cur_out_side_text_="";
    //用于每行的按钮
    enum{row_1, row_2, row_3, row_4, row_5};
    QMap<int, QList<MyVirtualKeyBoard_qBtn*>> btn_list_map_;

    enum{en0,en1,en2,ch0,ch1,ch2};//不同模式下按钮的显示文本，0代表没切换符号时的样子，1，2，3代表不同符号页面，
                                  //需要增加新符号则道init2()中去添加，
    int symbal_page_=en0;
    QMap<int, QStringList>symbol_list_map_={};
    void setSymbolPage(int enNum_chNum);//切换不同符号页

    enum{is_ch_mode,is_capital_mode};
    QMap<int, bool>mode_flag_map_{};


//    typedef  void (*setText_fp) (const QString&);
    QString objName_="";
//    QMap<QString, setText_fp>objName_fp_map_;
private slots:
    void showChinese(const QString &key, const QMap<int, QStringList> &chinese_list_map);
    void recKeyClicked(const QString &str);//处理所有虚拟键盘的按钮  -------------------------------------------------
    void selectChinese(const QString &ch);


    void show(const QString &curText, const QString &recObjName);
//    void show(const QString &curText, const QString &recObjName, setText_fp);

public slots:
    void show();
signals:
    void changedOutSideTextSignal(const QString &text, const QString &objName);//表示当前外部输入源文本已经被改变

};

#endif // VIRTUALKEYBOARD_H





























