#ifndef PREVIEWCOLORAREA_H
#define PREVIEWCOLORAREA_H

#include <QWidget>
#include <QStylePainter>

// 颜色预览区域
class PreviewColorArea : public QWidget
{
	Q_OBJECT

public:
    PreviewColorArea(QWidget *parent = nullptr);

    void setCurColor(const QColor &); // 设置当前颜色
    void setNewColor(const QColor &); // 设置新的颜色

protected:
	void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *);

public slots:
    void slotSvChanged(int, int, int);
	
signals:
    void sigSvChanged(int, int, int);

private:
    void paint(QPainter &painter, QRect) const;

	QColor m_curColor;
	QColor m_newColor;
};

#endif // PREVIEWCOLORAREA_H
