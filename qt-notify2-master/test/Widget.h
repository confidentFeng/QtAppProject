#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QBoxLayout>
#include <QMessageBox>
#include <QDialogButtonBox>
#include "NotifyManager.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);

signals:

};

#endif // WIDGET_H
