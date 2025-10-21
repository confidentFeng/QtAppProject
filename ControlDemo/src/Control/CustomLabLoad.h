#ifndef CUSTOMLABLOAD_H
#define CUSTOMLABLOAD_H

#include <QLabel>
#include <QTimerEvent>

// 自定义加载标签：显示多个设置图片，例如多个加载图片
class CustomLabLoad : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabLoad(QWidget *parent = nullptr);
    void setImageCount(const QString &imagePath, const int imageCount); // 设置图片路径和总数目
    void setInterval(const int &interval); // 设置定时间隔时间

protected:
    void timerEvent(QTimerEvent *event) override; // 定时器事件

private:
    int timerId;
    int m_nIndex = 0;
    QString m_imagePath = "";
    int m_imageCount = 1;
};

#endif // CUSTOMLABLOAD_H
