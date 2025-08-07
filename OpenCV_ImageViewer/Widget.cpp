#include "Widget.h"

// 将 OpenCV 的 Mat 转换为 Qt 的 QImage
QImage matToQImage(const cv::Mat& mat)
{
    switch (mat.type())
    {
    case CV_8UC1: // 8位灰度图
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
    case CV_8UC3: // 8位RGB图
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
    case CV_8UC4: // 8位RGBA图
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32).rgbSwapped();
    default:
        qWarning("Unsupported image format");
        return QImage();
    }
}

/**
 * @brief 滑动条的回调函数
 * @param pos 滑动条的当前位置
 */
cv::Mat rotateImage(cv::Mat src, int pos) {
    // 1. 获取旋转中心：图像的几何中心
    Point2f center(src.cols / 2.0F, src.rows / 2.0F);

    // 2. 计算旋转矩阵
    // 参数：旋转中心、旋转角度 (pos)、缩放因子 (1.0)
    Mat rot = getRotationMatrix2D(center, pos, 1.0);

    // 3. 计算旋转后图像的边界框，以防止图像被裁切
    // 获取旋转后的边界框
    Rect bbox = RotatedRect(center, src.size(), pos).boundingRect();
    // 调整旋转矩阵，加入平移变换，使得旋转后的图像能完整显示
    rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
    rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

    // 4. 应用仿射变换（旋转）
    // 参数：输入图像、输出图像、变换矩阵、输出图像尺寸
    cv::Mat dst;
    warpAffine(src, dst, rot, bbox.size());

    return dst;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 界面初始化
    this->setFixedSize(1200, 800);
    this->setAttribute(Qt::WA_StyledBackground); // 不继承父窗口样式
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true); // 设置鼠标穿透，避免其也响应鼠标进入事件

    // 图像Widget
    m_pImageWidget = new ImageWidget;
    m_pImageWidget->setFixedSize(640, 360);

    // 基本操作图像Widget
    m_pLabImgBasic = new QLabel;
    m_pLabImgBasic->setObjectName("LabImage");
    m_pLabImgBasic->setFixedSize(640, 360);

    // 打开图片
    m_pBtnOpen = new QPushButton;
    m_pBtnOpen->setObjectName("Common_BtnBlue_14px");
    m_pBtnOpen->setFixedSize(100, 30);
    m_pBtnOpen->setText(tr("打开图片"));
    // 恢复图片
    m_pBtnRestore = new QPushButton;
    m_pBtnRestore->setObjectName("Common_BtnBlue_14px");
    m_pBtnRestore->setFixedSize(100, 30);
    m_pBtnRestore->setText(tr("恢复图片"));
    // 关闭图片
    m_pBtnClose = new QPushButton;
    m_pBtnClose->setObjectName("Common_BtnBlue_14px");
    m_pBtnClose->setFixedSize(100, 30);
    m_pBtnClose->setText(tr("关闭图片"));
    // 分组框
    m_pGroupFile = new QGroupBox;
    m_pGroupFile->setFixedSize(140, 220);
    m_pGroupFile->setTitle(tr("打开文件"));
    // 按钮布局
    QVBoxLayout *pLayoutFile = new QVBoxLayout(m_pGroupFile);
    pLayoutFile->addSpacing(16);
    pLayoutFile->addWidget(m_pBtnOpen);
    pLayoutFile->addSpacing(16);
    pLayoutFile->addWidget(m_pBtnRestore);
    pLayoutFile->addSpacing(16);
    pLayoutFile->addWidget(m_pBtnClose);
    pLayoutFile->addStretch();
    pLayoutFile->setAlignment(Qt::AlignHCenter);
    pLayoutFile->setMargin(0);

    // 水平翻转
    m_pBtnFlipH = new QPushButton;
    m_pBtnFlipH->setObjectName("Common_BtnBlue_14px");
    m_pBtnFlipH->setFixedSize(100, 30);
    m_pBtnFlipH->setText(tr("水平翻转"));
    // 垂直翻转
    m_pBtnFlipV = new QPushButton;
    m_pBtnFlipV->setObjectName("Common_BtnBlue_14px");
    m_pBtnFlipV->setFixedSize(100, 30);
    m_pBtnFlipV->setText(tr("垂直翻转"));
    // 连续旋转文本
    m_pLabRotate = new QLabel;
    m_pLabRotate->setObjectName("Common_14pxTextBlack");
    m_pLabRotate->setText("旋转(0-90)");
    // 旋转滑动条
    m_pSliderRotate = new QSlider;
    m_pSliderRotate->setOrientation(Qt::Horizontal);  // 水平方向
    m_pSliderRotate->setMinimum(0);  // 最小值
    m_pSliderRotate->setMaximum(90);  // 最大值
    m_pSliderRotate->setSingleStep(1);  // 步长
    m_pSliderRotate->setFixedWidth(100); // 设置固定宽度，高度由样式表设置
    m_pSliderRotate->setValue(0);
    // 分组框
    m_pGroupTransform = new QGroupBox;
    m_pGroupTransform->setFixedSize(140, 220);
    m_pGroupTransform->setTitle(tr("几何变换"));
    // 按钮布局
    QVBoxLayout *pLayoutTransform = new QVBoxLayout(m_pGroupTransform);
    pLayoutTransform->addStretch();
    pLayoutTransform->addWidget(m_pBtnFlipH);
    pLayoutTransform->addStretch();
    pLayoutTransform->addWidget(m_pBtnFlipV);
    pLayoutTransform->addStretch();
    pLayoutTransform->addWidget(m_pLabRotate, 0, Qt::AlignCenter);
    pLayoutTransform->addSpacing(6);
    pLayoutTransform->addWidget(m_pSliderRotate);
    pLayoutTransform->addStretch();
    pLayoutTransform->setAlignment(Qt::AlignHCenter);
    pLayoutTransform->setMargin(0);

    // 初始化网格布局
    m_pLayoutGrid = new QGridLayout;
    m_pLayoutGrid->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_pLayoutGrid->setSpacing(4);
    m_pLayoutGrid->setMargin(4);
    m_pLayoutGrid->setGeometry(QRect(0,0,width(),height()));
    // 颜色列表
    QStringList colorList = {"0, 0, 0", "255, 255, 255", "255, 255, 0", "255, 0, 0",
                             "0, 0, 255", "0, 128, 0", "255, 165, 0", "128, 0, 128"};
    // 对颜色名列表进行遍历
    QString color;
    QStringList strList;
    foreach(color,colorList) {
        strList = color.split(",");
        BasicColorItem *pItem11 = new BasicColorItem(QColor(strList.at(0).toInt(), strList.at(1).toInt(), strList.at(2).toInt()));
        connect(pItem11, &BasicColorItem::sigItemClicked, this, &Widget::slotCreateImage);

        m_pLayoutGrid->addWidget(pItem11, m_pLayoutGrid->count()/4, m_pLayoutGrid->count()%4);
    }

    // 抠图
    m_pBtnMatting = new QPushButton;
    m_pBtnMatting->setObjectName("Common_BtnBlue_14px");
    m_pBtnMatting->setFixedSize(100, 30);
    m_pBtnMatting->setText(tr("抠图"));
    m_pBtnMatting->setCheckable(true);
    // 创建图像文本
    m_pLabCreateImg = new QLabel;
    m_pLabCreateImg->setObjectName("Common_14pxTextBlack");
    m_pLabCreateImg->setText("创建图像");
    // 分组框
    m_pGroupBasic = new QGroupBox;
    m_pGroupBasic->setFixedSize(140, 220);
    m_pGroupBasic->setTitle(tr("基本操作"));
    // 按钮布局
    QVBoxLayout *pLayoutBasic = new QVBoxLayout(m_pGroupBasic);
    pLayoutBasic->addSpacing(16);
    pLayoutBasic->addWidget(m_pBtnMatting, 0, Qt::AlignCenter);
    pLayoutBasic->addSpacing(16);
    pLayoutBasic->addWidget(m_pLabCreateImg, 0, Qt::AlignCenter);
    pLayoutBasic->addSpacing(4);
    pLayoutBasic->addLayout(m_pLayoutGrid);
    pLayoutBasic->addStretch();
    pLayoutBasic->setAlignment(Qt::AlignCenter);
    pLayoutBasic->setMargin(0);

    // 图像控件布局
    QVBoxLayout *pLayoutImage = new QVBoxLayout;
    pLayoutImage->addStretch();
    pLayoutImage->addWidget(m_pImageWidget);
    pLayoutImage->addSpacing(6);
    pLayoutImage->addWidget(m_pLabImgBasic);
    pLayoutImage->addStretch();
    pLayoutImage->setAlignment(Qt::AlignHCenter);
    pLayoutImage->setMargin(0);

    // 主布局
    QHBoxLayout *pLayoutMain = new QHBoxLayout(this);
    pLayoutMain->addSpacing(32);
    pLayoutMain->addLayout(pLayoutImage);
    pLayoutMain->addSpacing(32);
    pLayoutMain->addWidget(m_pGroupFile);
    pLayoutMain->addSpacing(32);
    pLayoutMain->addWidget(m_pGroupTransform);
    pLayoutMain->addSpacing(32);
    pLayoutMain->addWidget(m_pGroupBasic);
    pLayoutMain->addStretch();
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);

    // 在未打开图片前禁用所有控件
    setControlEnable(false);

    // 打开图片按钮-信号槽
    connect(m_pBtnOpen, &QPushButton::clicked, [=]{
        // 图片文件对话框
        QString imagePath = QFileDialog::getOpenFileName(this, tr("图片文件对话框"), "F:",tr("图片文件(* png * jpg)"));

        // 根据打开的图片路径读取图像
        m_matSrc = cv::imread(imagePath.toStdString().c_str());
        // 判断是否读取成功
        if(m_matSrc.data == NULL)
        {
            QMessageBox::information(this,"警告","图片读取失败，请检查图片路径！");
            return;
        }

        // 复制源图像到m_matDst（深拷贝）
        m_matDst = m_matSrc.clone();

        // 显示Mat图像
        showMatImage(m_matDst);

        // 在打开图片后使能所有控件
        setControlEnable(true);
    });

    // 恢复图片按钮-信号槽
    connect(m_pBtnRestore, &QPushButton::clicked, [=]{
        // 滑动条值清零
        m_pSliderRotate->setValue(0);

        // 复制源图像到m_matDst（深拷贝）
        m_matDst = m_matSrc.clone();

        // 显示Mat图像
        showMatImage(m_matDst);

        // 清空初始化
        m_pImageWidget->clear();
    });

    // 关闭图片按钮-信号槽
    connect(m_pBtnClose, &QPushButton::clicked, [=]{
        // 滑动条值清零
        m_pSliderRotate->setValue(0);

        m_matDst = cv::imread("");
        showMatImage(m_matDst);

        // 在关闭图片后禁用所有控件
        setControlEnable(false);

        // 清空初始化
        m_pImageWidget->clear();
    });

    // 水平翻转按钮-信号槽
    connect(m_pBtnFlipH, &QPushButton::clicked, [=]{
        // 水平翻转
        flip(m_matDst, m_matDst, 1);

        // 显示Mat图像
        showMatImage(m_matDst);
    });

    // 垂直翻转按钮-信号槽
    connect(m_pBtnFlipV, &QPushButton::clicked, [=]{
        // 垂直翻转
        flip(m_matDst, m_matDst, 0);

        // 显示Mat图像
        showMatImage(m_matDst);
    });

    // 旋转滑动条
    connect(m_pSliderRotate, &QSlider::valueChanged, [=](int value) {
        // 获取旋转后的目标Mat图像
        cv::Mat dst = rotateImage(m_matDst, value);

        // 显示Mat图像
        showMatImage(dst);
    });

    // 获取滚轮值改变目标图像的尺寸
    connect(m_pImageWidget, &ImageWidget::sigSendWheelVal, [=](const double &val){
        // 设置目标图像的尺寸
        cv::Mat dst;
        cv::Size newSize(m_matDst.size().width * val, m_matDst.size().height * val); // 新的宽度和高度
        cv::resize(m_matDst, dst, newSize);

        // 显示Mat图像
        showMatImage(dst);
    });

    // 发送截取区域矩形
    connect(m_pImageWidget, &ImageWidget::sigSendCaptureRect, [=](QRect rect) {
        m_captureRect = rect;

        // 安全检查：确保定义的 ROI 没有超出原始图像的边界
        if ((m_captureRect.x() + m_captureRect.width() > m_matDst.cols) ||
            (m_captureRect.y() + m_captureRect.height() > m_matDst.rows)) {
            std::cerr << "Error: The defined ROI exceeds the image boundaries!" << std::endl;
            return;
        }

        // 创建一个 cv::Rect 对象，指定 ROI 的位置和尺寸
        cv::Rect roiRect(m_captureRect.x(), m_captureRect.y(), m_captureRect.width(), m_captureRect.height());

        // 提取 ROI
        // 使用矩形对象来索引原始图像，创建一个指向 ROI 的 Mat 头
        cv::Mat roiImage = m_matDst(roiRect);

        // OpenCV 的 Mat 转换为 Qt 的 QImage
        QImage image = matToQImage(roiImage);

        // 显示结果
        m_pLabImgBasic->setPixmap(QPixmap::fromImage(image));

        return;
    });

    // 抠图按钮-信号槽
    connect(m_pBtnMatting, &QPushButton::clicked, [=]{
        if(m_pBtnMatting->isChecked()) {
            m_pBtnMatting->setText("抠图中");

            // 开始抠图
            m_pImageWidget->startMatting();
        }
        else {
            m_pBtnMatting->setText("抠图");

            // 结束抠图
            m_pImageWidget->endMatting();
        }
    });
}

Widget::~Widget()
{
}

// 创建图像
void Widget::slotCreateImage(const QColor &color)
{
    // 创建空白图像
    Mat createMat = Mat::zeros(Size(m_pLabImgBasic->width(), m_pLabImgBasic->height()), CV_8UC3); // 8uc1无符号8位，通道1
    createMat = Scalar(color.blue(), color.green(), color.red()); // 赋值 B G R

    // 将 OpenCV 的 Mat 转换为 Qt 的 QImage
    QImage image = matToQImage(createMat);

    // 显示结果
    m_pLabImgBasic->setPixmap(QPixmap::fromImage(image));
}

// 设置各控件使能
void Widget::setControlEnable(const bool &isEnable)
{
    m_pBtnRestore->setEnabled(isEnable);
    m_pBtnClose->setEnabled(isEnable);
    m_pBtnFlipH->setEnabled(isEnable);
    m_pBtnFlipV->setEnabled(isEnable);
    m_pSliderRotate->setEnabled(isEnable);
    m_pBtnMatting->setEnabled(isEnable);
}

// 显示Mat图像
void Widget::showMatImage(const Mat &mat)
{
    // 将 OpenCV 的 Mat 转换为 Qt 的 QImage
    QImage image = matToQImage(mat);

    // 转换原始图像
    QPixmap pixmap(QPixmap::fromImage(image));

    // 设置图像Widegt的图像pixmap
    m_pImageWidget->setPixmap(pixmap);
}

// 放大图像
void Widget::zoomInImage()
{
    m_zoomValue += 0.05;

    // 设置目标图像的尺寸
    cv::Mat dst;
    cv::Size newSize(m_matDst.size().width * m_zoomValue, m_matDst.size().height * m_zoomValue); // 新的宽度和高度
    cv::resize(m_matDst, dst, newSize);

    // 显示Mat图像
    showMatImage(dst);
}

// 缩小图像
void Widget::zoomOutImage()
{
    m_zoomValue -= 0.05;
    if(m_zoomValue <= 0)
        m_zoomValue = 0.05;

    // 设置目标图像的尺寸
    cv::Mat dst;
    cv::Size newSize(m_matDst.size().width * m_zoomValue, m_matDst.size().height * m_zoomValue); // 新的宽度和高度
    cv::resize(m_matDst, dst, newSize);

    // 显示Mat图像
    showMatImage(dst);
}
