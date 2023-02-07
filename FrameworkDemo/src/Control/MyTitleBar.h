#ifndef MYTITLEBAR_H
#define MYTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

// 自定义标题栏
class MyTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit MyTitleBar(QWidget *parent = nullptr);
    void setTitleName(const QString &sText); // 设置标题名称
    QString getTitleName(); // 获取标题名称
    void hideCloseBtn(const bool &isHide); // 隐藏关闭按钮

signals:
    void sigClose(); // 关闭信号

private:
    QLabel *m_pLabTitle;
    QPushButton *m_pBtnClose;
};

#endif // MYTITLEBAR_H
