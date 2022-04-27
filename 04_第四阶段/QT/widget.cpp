#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_bFlag(false)
{
    ui->setupUi(this);
    // 方法1
    // ui->labelAvantar->setStyleSheet("border-image: url(:/image/avantar.png)");
    // 方法2
    QPixmap pix(":/image/avantar.png");
    ui->labelAvantar->setPixmap(pix);
    // 按比例缩放
    ui->labelAvantar->setScaledContents(true);

    connect(ui->pushButton, &QAbstractButton::clicked,
            this, &Widget::slotShowTips);

    connect(ui->pushButton_2, &QAbstractButton::clicked,
            this, &Widget::slotClearTips);

    m_pMovie = new QMovie;
    m_pMovie->setFileName(":/image/123.gif");
    m_pMovie->setSpeed(1000);
    ui->labelAvantar->setMovie(m_pMovie);
}

void Widget::slotShowTips(){

    if(m_bFlag){
        ui->label->setText("登录失败!");
        // m_pMovie->stop();
        m_pMovie->setPaused(true);
    }
    else {
        ui->label->setText("登录成功!");
        m_pMovie->setPaused(false);
        // m_pMovie->start();
    }
    m_bFlag = !m_bFlag;
    //ui->label->setNum(20);
}

void Widget::slotClearTips(){
    // 清空文本
   ui->label->clear();
}

Widget::~Widget(){
    delete ui;
}
