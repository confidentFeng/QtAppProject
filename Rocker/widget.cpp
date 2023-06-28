#include "widget.h"

Widget::Widget(QDialog *parent)
    : QDialog(parent)
{
    Init(); //初始化函数
}

Widget::~Widget()
{

}

//初始化函数
void Widget::Init()
{
    //设置窗口无边框且窗口显示在最顶层
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);

    //设置大圆圆心位置
    SmallCir_xy.setX(300);
    SmallCir_xy.setY(300);
    //设置小圆圆心位置，与大圆相同
    BigCir_xy=SmallCir_xy;

    //设置窗口固定大小为400*400
    this->setFixedSize(400,400);

    //鼠标点击标志初始化
    MousePressFlag=false;
}

//绘图事件：绘制地图、摇杆中的大圆和小圆
void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    //绘图画笔
    QPainter painter(this);
    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);
    //消锯齿
    painter.setRenderHints(QPainter::SmoothPixmapTransform);

    //绘制摇杆中的大圆
    QPixmap bigCircle_Pixmap;
    bigCircle_Pixmap.load(":/new/prefix1/image/max.png");
    painter.drawPixmap(SmallCir_xy.x()-BIG_CIRCLE_RADIUS,SmallCir_xy.y()-BIG_CIRCLE_RADIUS,\
                       BIG_CIRCLE_RADIUS*2,BIG_CIRCLE_RADIUS*2,bigCircle_Pixmap);

    //绘制摇杆中的小圆
    QPixmap smallCircle_Pixmap;
    smallCircle_Pixmap.load(":/new/prefix1/image/min.png");
    painter.drawPixmap(BigCir_xy.x()-SMALL_CIRCLE_RADIUS,BigCir_xy.y()-SMALL_CIRCLE_RADIUS,\
                       SMALL_CIRCLE_RADIUS*2,SMALL_CIRCLE_RADIUS*2,smallCircle_Pixmap);
}

//鼠标移动事件：实现摇杆功能
void Widget::mouseMoveEvent(QMouseEvent *e)
{
    QPoint rocker_xy; //摇杆所在的实时坐标
    QByteArray xy;
    xy.resize(2);
    int x,y;
    rocker_xy=e->pos();

    if(MousePressFlag) //MousePressFlag为true，说明鼠标点击在了大圆内，才进行计算
    {
        //小圆圆心出了大圆则在大圆上90-25=65  65*65=4225
        if(pow((rocker_xy.x()-SmallCir_xy.x()),2)+pow((rocker_xy.y()-SmallCir_xy.y()),2)>8100)
        {
            x=int( 90*cos(atan2(abs(rocker_xy.y()-SmallCir_xy.y()),abs(rocker_xy.x()-SmallCir_xy.x()))) );
            y=int( 90*sin(atan2(abs(rocker_xy.y()-SmallCir_xy.y()),abs(rocker_xy.x()-SmallCir_xy.x()))) );

            //第一象限
            if(rocker_xy.x()>SmallCir_xy.x()&&rocker_xy.y()>SmallCir_xy.y())
            {
                BigCir_xy.setX(x+SmallCir_xy.x());
                BigCir_xy.setY(y+SmallCir_xy.y());
            }
            //第二象限
            else if(rocker_xy.x()<SmallCir_xy.x()&&rocker_xy.y()>SmallCir_xy.y())
            {
                BigCir_xy.setX(-x+SmallCir_xy.x());
                BigCir_xy.setY(y+SmallCir_xy.y());
                x=-x;
            }
            //第三象限
            else if(rocker_xy.x()<SmallCir_xy.x()&&rocker_xy.y()<SmallCir_xy.y())
            {
                BigCir_xy.setX(-x+SmallCir_xy.x());
                BigCir_xy.setY(-y+SmallCir_xy.y());
                x=-x;
                y=-y;
            }
            //第四象限
            else if(rocker_xy.x()>SmallCir_xy.x()&&rocker_xy.y()<SmallCir_xy.y())
            {
                BigCir_xy.setX(x+SmallCir_xy.x());
                BigCir_xy.setY(-y+SmallCir_xy.y());
                y=-y;
            }
        }
        else
        {
            BigCir_xy=rocker_xy;
            x=rocker_xy.x()-SmallCir_xy.x();
            y=rocker_xy.y()-SmallCir_xy.y();
        }
        xy[0]=char( x );
        xy[1]=char( y );
        //hex发送
        //mycartcp->TCPSend(xy);
        qDebug()<<x<<y;
        update();
    }

    MapRemov_Old=rocker_xy;
}

//鼠标释放事件：释放鼠标，则MousePressFlag复位，且小圆圆心设置为初始值，更新绘图事件后，重新绘图使小圆（摇杆）回到原处
void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);

    //释放鼠标，则MousePressFlag复位
    MousePressFlag=false;
    //小圆圆心设置为初始值,即大圆圆心值
    BigCir_xy.setX(SmallCir_xy.x());
    BigCir_xy.setY(SmallCir_xy.y());

    this->update(); //更新绘图事件后，重新绘图使小圆（摇杆）回到原处
}

//鼠标按下事件：获取摇杆所在的实时坐标
void Widget::mousePressEvent(QMouseEvent *e)
{
    QPoint rocker_xy; //摇杆所在的实时坐标

    rocker_xy=e->pos(); //获取摇杆所在的实时坐标
    qDebug() <<"摇杆坐标： " <<rocker_xy;

    //鼠标点击，在大圆内才设置MousePressFlag
    if(pow((rocker_xy.x()-SmallCir_xy.x()),2)+pow((rocker_xy.y()-SmallCir_xy.y()),2)<=8100) //判断摇杆是否在大圆内
    {
       MousePressFlag=true;
    }
    else
    {
       MapRemov_Old=rocker_xy;
    }
}
