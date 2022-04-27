#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(slotBtnClicked()));
    connect(this, SIGNAL(signalSendValue(int)), this, SLOT(slotRecieveValue(int)));
    //qDebug() << ui->pushButton_1->text();
    //qDebug() << ui->pushButton_2->text();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotBtnClicked()
{
    // emit用来发射自定义信号signalSendValue
    // 在这里:toInt是把字符串转换成整数的方法(QString自带的方法)
    emit signalSendValue(ui->pushButton_1->text().toInt());
}

void Widget::slotRecieveValue(int nValue)
{
    qDebug() << nValue;
}
