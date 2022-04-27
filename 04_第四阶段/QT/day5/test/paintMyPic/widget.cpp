#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p;
    p.begin(this);
    p.setPen(QPen(Qt::blue, 4, Qt::DashLine));    // 设置画笔形式
    p.drawRect(100, 100, 150, 100);
    p.end();

    QPainter p1;
    p1.begin(this);
    p1.setPen(QPen(Qt::lightGray, 3, Qt::DashDotDotLine));
    p1.drawEllipse(300, 300, 100, 100);
    p1.end();
}

Widget::~Widget()
{
    delete ui;
}
