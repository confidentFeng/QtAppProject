#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QPoint>
#include <QMovie>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QDebug>

class LoadingWidget : public QWidget
{
    Q_OBJECT
    // 声明属性
    Q_PROPERTY(int pixmap READ pixmap WRITE setPixmap)

public:
    explicit LoadingWidget(QWidget *parent = nullptr);
    void startAnimation(); // 开始动画
    void stopAnimation(); // 停止动画
    void setPixmap(const int &index); // 切换图标
    void setPixmapPath(const QString &pixmapPath, int pixmapCnt); // 设置图像路径

private:
    int pixmap() const; // 获取图像序号

    QLabel *m_pLoadingLabel;
    QPropertyAnimation *m_pAnimation;
    int m_nIndex;
    QString m_pixmapPath;
    int m_pixmapCnt;
};

#endif // LOADINGWIDGET_H
