#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QPushButton>
#include <QAction>
#include <QHBoxLayout>

// 自定义图标按钮
class CustomEditIcon : public QLineEdit
{
    Q_OBJECT
public:
    explicit CustomEditIcon(QWidget *parent = nullptr);
    void setLeftIcon(const QIcon &icon); // 设置左边图标
    void setClearBtnOffset(int offset); // 设置清除文本按钮的边距偏移量

protected:
    void resizeEvent(QResizeEvent *event) override; // 尺寸大小变化事件

private:
    QAction *m_pActionLeft;
    QPushButton *m_pBtnClear;

    int m_nClearBtnOffset = 8; // 偏移值：数越大文本越往前偏移，太大会遮挡清除按钮，适当调整
};

#endif // MYLINEEDIT_H
