#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QSlider>
#include <QProgressBar>
#include <QScrollBar>
#include <QApplication>
#include <QDebug>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLabel *m_pLabTest;
    QPushButton *m_pBtnTest;
    QLineEdit *m_pLineEdit;

    QCheckBox *m_pCheckBox;
    QProgressBar *m_pProBar;
    QSlider *m_pSlider;
    QScrollBar *m_pScrollBar;
};
#endif // WIDGET_H
