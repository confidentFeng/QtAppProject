#ifndef FUNC_H
#define FUNC_H

#include <QMutex>
#include <QDebug>

/*
作用： 解决QT4、QT5中文显示乱码的问题
*/


//#define QT4 1
#define QT5 1


#ifdef QT4
#include <QApplication>
void setFontPath(const QString &font_path, QApplication &a);
#endif

#ifdef QT5
void setFontPath(const QString& font_path);
#endif











#endif // FUNC_H
