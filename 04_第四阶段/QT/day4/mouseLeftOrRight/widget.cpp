#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        qDebug() << "LeftButton is clicked";
    if(event->button()==Qt::RightButton)
        qDebug() << "RightButton is clicked";
}

Widget::~Widget()
{
    delete ui;
}
