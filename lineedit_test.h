#ifndef LINEEDIT_TEST_H
#define LINEEDIT_TEST_H

#include<QLineEdit>

class LineEdit_test:public QLineEdit
{
    Q_OBJECT
public:
    LineEdit_test(QWidget *parent = nullptr);




protected:
    void mousePressEvent(QMouseEvent *e) override;
signals:
    void curTextSignal(const QString &curText, const QString &curObjName);
public slots:
    void setTextSlot(const QString& text, const QString &ObjName);
};

#endif // LINEEDIT_TEST_H
