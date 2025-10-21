#include "CustomLabLoad.h"

CustomLabLoad::CustomLabLoad(QWidget *parent) : QLabel(parent)
{

}

// 设置图片路径和总数目
void CustomLabLoad::setImageCount(const QString &imagePath, const int imageCount)
{
    m_imagePath = imagePath;
    m_imageCount = imageCount;
}

void CustomLabLoad::setInterval(const int &interval)
{
    // 初始化定时器id
    timerId = startTimer(interval/m_imageCount);
}

// 定时器事件
void CustomLabLoad::timerEvent(QTimerEvent *event)
{
    // timerEvent事件最好不要处理过久，因为如果这个事件函数被占用了，下一次的startTimer定时器事件也会无法响应
    if(event->timerId() == timerId) {
        // 若当前图标下标超过8表示到达末尾，重新计数
        m_nIndex++;
        if (m_nIndex > m_imageCount)
            m_nIndex = 1;

        QPixmap pixmap(m_imagePath + QString("%1").arg(m_nIndex));
        this->setPixmap(pixmap);
    }
}
