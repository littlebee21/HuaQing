#include "widget.h"
#include "ui_widget.h"
#include <QDebug>


// 这是Widget类的构造函数
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_nCounter = 1;
    // connect(sender, SIGNAL(signal), reciever, SLOT(slot));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slotPrintText()));
    // connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slotPrintText2()));

    // 信号关联信号
    connect(ui->concernBtn, SIGNAL(clicked()), this, SIGNAL(signalClickeSend()));
    connect(this, SIGNAL(signalClickeSend()), this, SLOT(slotConcernAnotherSignal()));
}

// slot的实现
void Widget::slotPrintText(){
    qDebug() << "Hello world" << "-----" << m_nCounter;
    m_nCounter++;
}

void Widget::slotPrintText2()
{
    qDebug() << "你好" << "-----" << m_nCounter;
    m_nCounter++;
}

void Widget::slotConcernAnotherSignal()
{
    qDebug() << "信号关联信号";
}

Widget::~Widget()
{
    delete ui;
}
