#ifndef MUSICLISTWIDGET_H
#define MUSICLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include "src/TableView/MTableDelegate.h"
#include "src/TableView/MTableModel.h"

// 音乐列表
class MusicListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicListWidget(QWidget *parent = nullptr);

private:

};

#endif // MUSICLISTWIDGET_H
