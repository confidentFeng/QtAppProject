#ifndef CAROUSELPANE_H
#define CAROUSELPANE_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPushButton>

// 轮播图界面
class CarouselWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CarouselWidget(QWidget *parent = 0);

public:
    void SetImageList(QStringList listImgFileName);
    void StartPlay();

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();
    void UpdateChangeBtns();

    void paintEvent(QPaintEvent *event);

private slots:
    void OnImageChangeTimeout();
    void OnImageSwitchButtonClicked(int nIndex);

private:
    QTimer *m_pTimerImageChange;
    QPropertyAnimation* m_pAnimationOpacity;
    QList<QPushButton*> m_listBtns;

    int m_nCurrentImageIndex;
    QPixmap m_pixCurrent;
    QPixmap m_pixNext;
    QList<QString> m_listImgFileName;
};

#endif // CAROUSELPANE_H
