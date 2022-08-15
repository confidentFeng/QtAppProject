#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <QWidget>
#include <QTranslator>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QEvent>
#include <QApplication>
#include <QDebug>

class Translate : public QWidget
{
    Q_OBJECT

public:
    Translate(QWidget *parent = nullptr);
    void setTranslator(QTranslator* translator); // 设置翻译对象

protected:
    void changeEvent(QEvent *event); // 改变事件

private:
    void translateUI(); // 统一设置需要被翻译的文本

    QLabel *m_pLabText;
    QComboBox *m_pComboBox;
    QTranslator *m_translator; // 国际化翻译对象
};
#endif // TRANSLATE_H
