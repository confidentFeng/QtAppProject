#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "ColorSelWidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    QPushButton *m_pBtnClor;

    ColorSelWidget *m_pColorSelWidget;
};
#endif // MAINWIDGET_H
