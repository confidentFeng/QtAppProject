#include "showmap.h"
#include "ui_showmap.h"

ShowMap::ShowMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowMap)
{
    ui->setupUi(this);

    //初始化窗口
    Init();
}

ShowMap::~ShowMap()
{
    delete ui;
}

//初始化窗口
void ShowMap::Init()
{
    //设置窗口无边框且窗口显示在最顶层
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);

    //巡航点GroupBox
    ui->cruiseGroupBox->setGeometry(20,176,296,386);
    ui->cruiseGroupBox->hide();

    //初始化地图图片
    pix.load(":/new/prefix1/image/map.png");
    //pix.load(":/new/prefix1/image/map.pgm");
    //初始化地图图片的原始尺寸
    OriginSize.setX(pix.width());
    OriginSize.setY(pix.height());
    //初始化地图图片的实时尺寸
    CurrImgSize.setX(OriginSize.x());
    CurrImgSize.setY(OriginSize.y());
    //初始化地图图片的绘制原点
    ImgPaintOrigin.setX(-(OriginSize.x()-WINDOW_WIDTH)/2);
    ImgPaintOrigin.setY(-(OriginSize.y()-WINDOW_HEIGHT)/2);

    //初始化中心点坐标
    CentPoint_xy.setX(WINDOW_WIDTH/2);
    CentPoint_xy.setY(WINDOW_HEIGHT/2);
    //初始化鼠标全部移动坐标
    MouseAllMove_x = 0;
    MouseAllMove_y = 0;
    //初始化放大缩小次数
    AddLessCount = 0;

    //初始化预设点设置相关定时器：防止鼠标移动前的鼠标按下，错误更新预设点绘制坐标
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(doProssTimerOut()),Qt::UniqueConnection);

    this->update();
}

//绘图事件：绘制地图图片、预设点
void ShowMap::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); //抗锯齿
    painter.setRenderHints(QPainter::SmoothPixmapTransform); //消锯齿

    //绘制地图图片（绘制原点可以是窗口负坐标，即窗口左上角未显示区域）
    painter.drawPixmap(ImgPaintOrigin.x(),ImgPaintOrigin.y(),CurrImgSize.x(),CurrImgSize.y(),pix);

    //绘制设定点
    QPen pen;
    QPixmap pixPoint;
    pixPoint.load(":/new/prefix1/image/point.png");
    if(PreSetPoint_xy.x()!=0 && PreSetPoint_xy.y()!=0) //不允许在原点(0,0)上画点
    {
        //绘制设定点（设定点图片大小为44*44，绘制起点是图片的左上角坐标）
        painter.drawPixmap(PreSetPoint_xy.x()-pixPoint.width()/2,PreSetPoint_xy.y()-pixPoint.height(),pixPoint.width(),pixPoint.height(),pixPoint);
    }

    //绘制设置点和设置点序号
    pen.setColor(Qt::red);
    painter.setPen(pen);
    QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);
    for(int i=0;i<Point_xy.count();i++)
    {
        //绘制设置点
        painter.drawPixmap(Point_xy.at(i).x()-22,Point_xy.at(i).y()-44,44,44,pixPoint);
        //绘制设置点序号
        painter.drawText(Point_xy.at(i).x()-5,Point_xy.at(i).y()-22,QString::number(i));
    }

    //绘制设置点连线
    pen.setColor(QColor(85,255,255));
    pen.setStyle(Qt::DotLine);
    pen.setWidth(3);
    painter.setPen(pen);
    if(Point_xy.count()>1)
    {
        for(int i=0;i<Point_xy.count()-1;i++)
        {
            painter.drawLine(Point_xy.at(i),Point_xy.at(i+1));
        }
    }
}

//放大背景图按钮-点击槽函数
void ShowMap::on_addBoardButton_clicked()
{
    //只允许放大3次
    if(AddLessCount<3)
    {
        //放大缩小次数加一
        AddLessCount++;

        //设置地图图片的绘制原点
        ImgPaintOrigin.setX( int(-(OriginSize.x()*pow(2,AddLessCount)-WINDOW_WIDTH)/2) );
        ImgPaintOrigin.setY( int(-(OriginSize.y()*pow(2,AddLessCount)-WINDOW_HEIGHT)/2) );
        //设置地图图片的绘制长宽
        CurrImgSize.setX(CurrImgSize.x()*2);
        CurrImgSize.setY(CurrImgSize.y()*2);

        //在放大缩小前，使中心点、预设点和设置点绘制坐标，还原成鼠标移动前的大小
        CentPoint_xy.setX(CentPoint_xy.x() - MouseAllMove_x);
        CentPoint_xy.setY(CentPoint_xy.y() - MouseAllMove_y);
        PreSetPoint_xy.setX(PreSetPoint_xy.x() - MouseAllMove_x);
        PreSetPoint_xy.setY(PreSetPoint_xy.y() - MouseAllMove_y);
        for(int i=0;i<Point_xy.count();i++)
        {
            Point_xy[i].setX(Point_xy[i].x() - MouseAllMove_x);
            Point_xy[i].setY(Point_xy[i].y() - MouseAllMove_y);
        }
        //清零鼠标全部移动坐标
        MouseAllMove_x = 0;
        MouseAllMove_y = 0;
        //使预设点坐标在放大时位置不改变（放大缩小后，预设点要求相对地图位置不变）
        PreSetPoint_xy.setX(PreSetPoint_xy.x()*2-CentPoint_xy.x());
        PreSetPoint_xy.setY(PreSetPoint_xy.y()*2-CentPoint_xy.y());
        //使设置点Point列表的各点，在放大时位置不改变
        for(int i=0;i<Point_xy.count();i++)
        {
            //使设定点坐标在放大时位置不改变
            Point_xy[i].setX(Point_xy[i].x()*2-CentPoint_xy.x());
            Point_xy[i].setY(Point_xy[i].y()*2-CentPoint_xy.y());
        }

        this->update();
    }
}

//缩小背景图按钮-点击槽函数
void ShowMap::on_lessBoardButton_clicked()
{
    //图片若小于等于MAP_WIDTH*MAP_HEIGHT，则说明是原尺存没有放大，不可以缩小，否则可以正常缩小
    if(CurrImgSize.x()>OriginSize.x()&&CurrImgSize.y()>OriginSize.y())
    {
        //放大缩小次数减一
        AddLessCount--;

        //设置图片绘制原点
        ImgPaintOrigin.setX( int(-(OriginSize.x()*pow(2,AddLessCount)-WINDOW_WIDTH)/2) );
        ImgPaintOrigin.setY( int(-(OriginSize.y()*pow(2,AddLessCount)-WINDOW_HEIGHT)/2) );
        //设置图片绘制长宽
        CurrImgSize.setX(CurrImgSize.x()/2);
        CurrImgSize.setY(CurrImgSize.y()/2);

        //在放大缩小前，使中心点、预设点和设置点绘制坐标，还原成鼠标移动前的大小
        CentPoint_xy.setX(CentPoint_xy.x() - MouseAllMove_x);
        CentPoint_xy.setY(CentPoint_xy.y() - MouseAllMove_y);
        PreSetPoint_xy.setX(PreSetPoint_xy.x() - MouseAllMove_x);
        PreSetPoint_xy.setY(PreSetPoint_xy.y() - MouseAllMove_y);
        for(int i=0;i<Point_xy.count();i++)
        {
            Point_xy[i].setX(Point_xy[i].x() - MouseAllMove_x);
            Point_xy[i].setY(Point_xy[i].y() - MouseAllMove_y);
        }
        //清零鼠标全部移动坐标
        MouseAllMove_x = 0;
        MouseAllMove_y = 0;
        //使预设点坐标在缩小时位置不改变
        PreSetPoint_xy.setX((PreSetPoint_xy.x()+CentPoint_xy.x())/2);
        PreSetPoint_xy.setY((PreSetPoint_xy.y()+CentPoint_xy.y())/2);
        //使设置点Point列表的各点，在缩小时位置不改变
        for(int i=0;i<Point_xy.count();i++)
        {
            //使设定点坐标在缩小时位置不改变
            Point_xy[i].setX((Point_xy[i].x()+CentPoint_xy.x())/2);
            Point_xy[i].setY((Point_xy[i].y()+CentPoint_xy.y())/2);
        }

        this->update();
    }
}

//复位背景图按钮-点击槽函数
void ShowMap::on_resetBoardButton_clicked()
{
    //设置地图图片的绘制原点
    ImgPaintOrigin.setX( int(-(OriginSize.x()*pow(2,0)-WINDOW_WIDTH)/2) );
    ImgPaintOrigin.setY( int(-(OriginSize.y()*pow(2,0)-WINDOW_HEIGHT)/2) );
    //设置地图图片的绘制长宽
    CurrImgSize.setX(OriginSize.x());
    CurrImgSize.setY(OriginSize.y());

    //在复位前，使预设点和设置点绘制坐标，还原成鼠标移动前的大小
    PreSetPoint_xy.setX(PreSetPoint_xy.x() - MouseAllMove_x);
    PreSetPoint_xy.setY(PreSetPoint_xy.y() - MouseAllMove_y);
    for(int i=0;i<Point_xy.count();i++)
    {
        Point_xy[i].setX(Point_xy[i].x() - MouseAllMove_x);
        Point_xy[i].setY(Point_xy[i].y() - MouseAllMove_y);
    }
    //清零鼠标全部移动坐标
    MouseAllMove_x = 0;
    MouseAllMove_y = 0;
    //复位中心点坐标
    CentPoint_xy.setX(WINDOW_WIDTH/2);
    CentPoint_xy.setY(WINDOW_HEIGHT/2);
    //逐次缩小,使预设点不变
    for(int j=0;j<AddLessCount;j++)
    {
        //使预设点坐标在复位时位置不改变（有问题，无效）
        PreSetPoint_xy.setX((PreSetPoint_xy.x()+CentPoint_xy.x())/2);
        PreSetPoint_xy.setY((PreSetPoint_xy.y()+CentPoint_xy.y())/2);
        //使设置点Point列表的各点，在复位时位置不改变
        for(int i=0;i<Point_xy.count();i++)
        {
            Point_xy[i].setX((Point_xy[i].x()+CentPoint_xy.x())/2);
            Point_xy[i].setY((Point_xy[i].y()+CentPoint_xy.y())/2);
        }
    }

    //放大缩小次数清零
    AddLessCount = 0;

    this->update();
}

//鼠标按下事件
void ShowMap::mousePressEvent(QMouseEvent *e)
{
    //获得鼠标点击坐标
    QPoint mousexy;
    mousexy = e->pos();
    //qDebug() << mousexy;

    MapRemov_Old = mousexy;

   //鼠标按下后打开定时器，500ms后超时绘制预设点
    if(timer->timerId() == -1)
        timer->start(500);

   //不能在这里直接将鼠标点击坐标，赋给预设点绘制坐标，因为后面移动图片前也会点击鼠标，
   //也要在鼠标移动事件关闭定时器，这样鼠标移动就不会修改预设点坐标了
   MousePress_xy = mousexy;
}

//鼠标移动事件
void ShowMap::mouseMoveEvent(QMouseEvent *e)
{
    //当前鼠标按下坐标
    QPoint mousexy;
    mousexy = e->pos();

    //鼠标(单次)移动坐标 = 图片移动距离 = 移动中的连续鼠标坐标减去移动前按下的仅一次鼠标坐标
    QPoint MouseMovePoint;
    MouseMovePoint.setX(mousexy.x()-MapRemov_Old.x());
    MouseMovePoint.setY(mousexy.y()-MapRemov_Old.y());

    //地图图片绘制原点坐标
    int xImgOrigin = ImgPaintOrigin.x() + MouseMovePoint.x();
    int yImgOrigin = ImgPaintOrigin.y() + MouseMovePoint.y();

    //当地图图片左上角坐标在(-(pow(2,AddLessCount)-1)*width,-(pow(2,AddLessCount)-1)*height))与(0,0)之间才可拖动图片
    if((xImgOrigin>=-(pow(2,AddLessCount)-1)*OriginSize.x() && yImgOrigin>=-(pow(2,AddLessCount)-1)*OriginSize.y()) \
            && (xImgOrigin<=0 && yImgOrigin<=0) )
    {
        //获得鼠标全部移动坐标
        MouseAllMove_x += MouseMovePoint.x();
        MouseAllMove_y += MouseMovePoint.y();

        //地图图片绘制坐标随图片移动
        ImgPaintOrigin.setX(xImgOrigin);
        ImgPaintOrigin.setY(yImgOrigin);

        //维持地图图片中心点坐标
        CentPoint_xy.setX(CentPoint_xy.x()+MouseMovePoint.x());
        CentPoint_xy.setY(CentPoint_xy.y()+MouseMovePoint.y());
        //预设点绘制坐标随图片移动
        PreSetPoint_xy.setX(PreSetPoint_xy.x()+MouseMovePoint.x());
        PreSetPoint_xy.setY(PreSetPoint_xy.y()+MouseMovePoint.y());
        for(int i=0;i<Point_xy.count();i++)
        {
            Point_xy[i].setX(Point_xy[i].x() + MouseMovePoint.x());
            Point_xy[i].setY(Point_xy[i].y() + MouseMovePoint.y());
        }

        this->update();
    }

    //移动鼠标前会点击鼠标，打开定时器，所以在这里要关闭先前打开的定时器
    timer->stop();

    MapRemov_Old = mousexy;
}

//超时函数：超时后将当前鼠标按下坐标，赋给预设点绘制坐标
void ShowMap::doProssTimerOut()
{
    //防止重复进入
    timer->stop();

    //超时后将当前鼠标按下坐标，赋给预设点绘制坐标
    PreSetPoint_xy = MousePress_xy;

    //更新绘图事件，绘制预设点
    this->update();
}

//手动按钮-点击槽函数
void ShowMap::on_manualButton_clicked()
{
    //隐藏groupBox，显示巡航点设置Group
    ui->groupBox->hide();
    ui->cruiseGroupBox->show();
}

//手动模式添加巡航点按钮-点击槽函数
void ShowMap::on_addItemButton_clicked()
{
    //当前点和设定点列表最后一个点相同则不能添加,原点也不能添加
    if( (Point_xy.count()>0 && Point_xy.last()==PreSetPoint_xy) || (PreSetPoint_xy.x()==0 && PreSetPoint_xy.y()==0) )
    {
        return;
    }

    //当listWidget没有列表项时，在设定点列表后添加项
    if(ui->listWidget->currentRow() == -1)
    {
        Point_xy.append(PreSetPoint_xy);
    }
    //当listWidget有列表项时，在设定点列表后面插入项
    else
    {
        Point_xy.insert(ui->listWidget->currentRow()+1, PreSetPoint_xy);
    }
    ui->listWidget->clear();

    //在listWidget上逐行添加项
    for(int i=0;i<Point_xy.count();i++)
    {
        ui->listWidget->addItem(QString::number(i) + "        " + QString::number(Point_xy[i].x()) + "-" + QString::number(Point_xy[i].y()));
    }

    this->update();
}

//巡航分组框的返回按钮-点击槽函数
void ShowMap::on_cruiseGroupBox_returnBtn_clicked()
{
    ui->cruiseGroupBox->hide();
    ui->groupBox->show();
}

//手动模式删除巡航点按钮-点击槽函数
void ShowMap::on_lessItemButton_clicked()
{
    //如果没有选中
    if(ui->listWidget->currentRow()==-1)
    {
        //删除最后一个点
        Point_xy.removeAt(Point_xy.count()-1);
    }
    //选中
    else
    {
        //删除当前所选点
        Point_xy.removeAt(ui->listWidget->currentRow());
    }
    ui->listWidget->clear();

    for(int i=0;i<Point_xy.count();i++)
    {
        ui->listWidget->addItem(QString::number(i)+"        "+QString::number(Point_xy[i].x())+"-"+QString::number(Point_xy[i].y()));
    }

    //清除当前点
    PreSetPoint_xy.setX(0);
    PreSetPoint_xy.setY(0);
    this->update();
}
