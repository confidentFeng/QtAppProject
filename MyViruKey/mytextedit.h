#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>

class mytextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit mytextEdit(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *e) override;
signals:
    void curTextSignal(const QString &curText, const QString &curObjName);

public slots:
    void setTextSlot(const QString& text, const QString &ObjName);

private:
};

#endif // MYTEXTEDIT_H
