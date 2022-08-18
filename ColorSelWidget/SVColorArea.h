#ifndef SVCOLORAREA_H
#define SVCOLORAREA_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QtMath>

// 功能：界面中的饱和度(S)与亮度(V)区域
class SVColorArea : public QWidget
{
	Q_OBJECT

public:
    SVColorArea(QWidget *parent = nullptr);
	void setHue(int);
	void setSaturation(int);
	void setBrightness(int);
	void setHsv(int, int, int);
	void setColor(const QColor &);

protected:
    void paintEvent(QPaintEvent *);			// 绘图事件
    void mousePressEvent(QMouseEvent *);	// 鼠标按下事件
    void mouseMoveEvent(QMouseEvent *);		// 鼠标移动事件

public slots:
    void slotHueChanged(int); // 色调改变的槽函数

signals:
    void sigSvChanged(int, int, int);

private:
    void drawSVPixmap();
    void createVPixmap();	// 创建亮度渐变的pixmap
    void createSVPixmap();	// 创建正方形区域的pixmap
    void updateSVPixmap();	// 更新正方形区域的pixmap

	int m_iHue;
	int m_iSaturation;
	int m_iBrightness;
    const int m_iAreaWidth;	// 正方形区域的宽度
    QPixmap m_svPixmap;	// 正方形区域的pixmap
    QPixmap m_vPixmap;	// 亮度渐变的pixmap
};

#endif // SVCOLORAREA_H
