#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    m_bFlag(true),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label->setScaledContents(false);
    //把label的属性背景透明度设置为透明，注意这并不能使你的图片变为透明，因为这只是使得label的边框，背景色彩消失而已。
    ui->label->setAttribute(Qt::WA_TranslucentBackground, true);
    pEffect = new QGraphicsOpacityEffect();
    pEffect->setOpacity(opacity);//透明范围为0.0-1.0，默认为0.7
    ui->label->setGraphicsEffect(pEffect);
    QPixmap pix("H:/Qtproject/test/danrudanchu/tupian.jpg");
    ui->label->setPixmap(pix);

    ui->label->show();
    //danruinit();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::danruinit()
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "windowOpacity");
    pAnimation->setDuration(2000);
    pAnimation->setStartValue(0);
    pAnimation->setEndValue(1);
    pAnimation->start();
}

void Widget::fadeIn()   // 淡入
{
    if(opacity>=1.0)
        timer1.stop();   // 定时器停止
    else
    {
        pEffect->setOpacity(opacity);
        ui->label->setGraphicsEffect(pEffect);
    }
    opacity += 0.05;    // 透明度减少
}

void Widget::fadeOut()  // 淡出
{
    if(opacity>=1.0)
        timer2.stop();   // 定时器停止
    else
    {
        pEffect->setOpacity(opacity);
        ui->label->setGraphicsEffect(pEffect);
    }
    opacity -= 0.05;    // 透明度增加
}

void Widget::on_pushButton_clicked()
{
    QObject::connect(&timer1,SIGNAL(timeout()),this,SLOT(fadeIn()));
    timer1.start(150);// 每隔150毫秒发射一次timeout()
}


void Widget::on_pushButton_2_clicked()
{
    // 利用QTimer实现渐变过程
    QObject::connect(&timer2,SIGNAL(timeout()),this,SLOT(fadeOut()));
    timer2.start(150);// 每隔150毫秒发射一次timeout()
}
