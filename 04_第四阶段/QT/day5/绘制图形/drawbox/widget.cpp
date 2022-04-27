#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setGeometry(100,100,200,200);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
#if 0
    painter = new QPainter;
    painter->begin(this);
    painter->setPen(QPen(Qt::blue,4,Qt::DashLine));//设置画笔形式
    //painter->setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式
    //painter->drawRect(20,20,160,160);
    painter->drawRoundedRect(20,20,160,160, 20, 20);
    painter->end();

    QPainter *painter1 = new QPainter;
    painter1->begin(this);
    painter1->setPen(QPen(Qt::blue,4,Qt::SolidLine));
    painter1->setBrush(QBrush(Qt::red,Qt::SolidPattern));
    painter1->drawEllipse(120,120,210,210);
    //painter1->drawPie(20,20,210,160,0,500);   // 扇形
#endif

    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,4));//设置画笔形式
    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    painter.drawLine(20,20,220,220);//画直线
    painter.drawLine(20,220,220,20);
    painter.drawEllipse(20,20,200,200);//画圆
    painter.drawRect(20,20,200,200);//画矩形
}
