#ifndef MyVirtualKeyboard_qLb_H
#define MyVirtualKeyboard_qLb_H

#include <QLabel>
class MyVirtualKeyboard_qLb : public QLabel
{
    Q_OBJECT
public:
    explicit MyVirtualKeyboard_qLb(QWidget *parent = nullptr);
    void setText(const QString &text);
signals:

public slots:

    void clear();

};

#endif // MyVirtualKeyboard_qLb_H
