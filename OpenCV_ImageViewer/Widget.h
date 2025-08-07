#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QImage>
#include <QWheelEvent>
#include <QGridLayout>
#include <QDebug>
#include "./ImageWidget.h"
#include "./BasicColorItem.h"

// 添加OpenCV相关头文件
#include <opencv2/opencv.hpp>
using namespace cv;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void slotCreateImage(const QColor &color);  // 创建图像

private:
    void setControlEnable(const bool &isEnable); // 设置各控件使能
    void showMatImage(const cv::Mat& mat); // 显示Mat图像
    void zoomInImage(); // 放大图像
    void zoomOutImage(); // 缩小图像

    ImageWidget *m_pImageWidget; // 图像Widget
    QLabel *m_pLabImgBasic; // 基本操作图像Widget

    cv::Mat m_matSrc; // 源图片mat
    cv::Mat m_matDst; // 目标图片mat

    QPushButton *m_pBtnOpen; // 打开图片
    QPushButton *m_pBtnRestore; // 恢复图片
    QPushButton *m_pBtnClose; // 关闭图片
    QGroupBox *m_pGroupFile; // 文件操作

    QPushButton *m_pBtnFlipH; // 水平翻转
    QPushButton *m_pBtnFlipV; // 垂直翻转
    QLabel *m_pLabRotate; // 连续旋转文本
    QSlider *m_pSliderRotate; // 旋转滑动条
    QGroupBox *m_pGroupTransform; // 几何变换

    QPushButton *m_pBtnMatting; // 抠图
    QLabel *m_pLabCreateImg; // 创建图像文本
    QGridLayout *m_pLayoutGrid; // 网格布局
    QGroupBox *m_pGroupBasic; // 基本操作

    qreal m_zoomValue = 1.0;  // 鼠标缩放值
    QRect m_captureRect; // 截取区域
};
#endif // MAINWINDOW_H
