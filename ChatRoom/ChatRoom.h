#ifndef CHATROOM_H
#define CHATROOM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextBrowser>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDateTime>
#include <QTimer>

class MeetChatRoom : public QWidget
{
    Q_OBJECT

public:
    MeetChatRoom(QWidget *parent = nullptr);

private:
    QWidget *m_pWidgetTitle;
    QLabel *m_pLabIcon; // 图标标签
    QLabel *m_pLabTtile; // 标题标签
    QPushButton *m_pBtnClose; // 关闭按钮
    QTextBrowser *m_pTextBrowser; // 作为聊天文本显示区域
    QTextEdit *m_pTextEdit; // 作为聊天文本输入区域
    QPushButton *m_pBtnSend; // 发送按钮

    QTimer *m_pTimer;
    bool m_isEnableTime = true;
};
#endif // CHATROOM_H
