#ifndef MyVirtualKeyBoard_qBtn_H
#define MyVirtualKeyBoard_qBtn_H

#include <QPushButton>
//  解决段时间连续点击按钮
//  对按钮的不同操作
//
class QLabel;
class MyVirtualKeyBoard_qBtn : public QPushButton
{

    Q_OBJECT
public:
    explicit MyVirtualKeyBoard_qBtn(QWidget *parent = nullptr);

    void setText(const QString &text);

protected:
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );

private:
    QPoint pos2_;
    QTimer* timer_=nullptr;
    QTimer* is_press_on_timer_=nullptr;
    bool is_ok_=true;
    bool is_press_on_=false;
//    bool text_is_empty_=true;
signals:
    void clicked(const QString&);
//    void mouse_command(int flag);
//    void mouse_ok_release(/*int unused = default_ret*/);//在按钮内释放
private slots:
    void updatePressStatus();
    void pressOnSlot();

public slots:


};

#endif // MyVirtualKeyBoard_qBtn_H
