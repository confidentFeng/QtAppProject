#ifndef TOOLPAGE_H
#define TOOLPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QDebug>

class QFormLayout;
class QLabel;
class ToolPage : public QWidget
{
    Q_OBJECT

public:
    explicit ToolPage(QWidget *parent = nullptr);

public slots:
    void addWidget(const QString &title, QWidget *widget); // 添加界面
    void expand();
    void collapse();

private:
    QLabel *m_pLabIcon; // 图标标签
    QPushButton *m_pBtnFold; // 折叠按钮
    QWidget *m_pWidgetContent; // 内容子界面
    QVBoxLayout *m_pLayoutContent; // 内容子界面布局

    bool m_bIsExpanded = true; // 是否折叠
};

#endif // TOOLPAGE_H
