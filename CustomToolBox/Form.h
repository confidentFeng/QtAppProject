#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QButtonGroup>

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr, QStringList btnNameList = QStringList());
    void setUncheckAll(); // 取消所有按钮的选中状态

signals:
    void sigChecked();

private:
    QVBoxLayout *m_pLayoutMain; // 主布局
    QButtonGroup *m_pGroupBox; // 按钮组

    QPushButton *m_pBtnOther; // 其他按钮
};

#endif // FORM_H
