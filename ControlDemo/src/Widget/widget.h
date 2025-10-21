#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QLineEdit>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLabel* m_message;
    QPropertyAnimation* m_messageAntF;
    QPropertyAnimation* m_messageAntB;
    QSequentialAnimationGroup* m_messageAntG;
    QLineEdit* m_msgEdit;
    QPushButton* m_successBtn;
    QPushButton* m_errorBtn;

    void alertSuccess(const QString& text);
    void alertError(const QString& text);
};
#endif // WIDGET_H
