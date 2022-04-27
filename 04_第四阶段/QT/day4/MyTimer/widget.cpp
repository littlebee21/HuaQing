#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label->setNum(m_nCount);
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::slotBtnClicked);
}

void Widget::slotCloseWidget()
{
    close();
}

void Widget::slotShowLabelCount()
{
    m_nCount--;
    ui->label->setNum(m_nCount);
}

void Widget::slotBtnClicked()
{
    // 为什么要在这里创建:
    // 因为使用的时候再初始化会减轻应用程序初始化时候的负担
//    m_pTimer = new QTimer(this);
//    m_pTimer->start(3000);
//    connect(m_pTimer, &QTimer::timeout, this, &Widget::slotCloseWidget);

//    // QTimer *pTimerLabelCount = new QTimer(this);
//    // pTimerLabelCount->start(1000);
//    // connect(pTimerLabelCount, &QTimer::timeout, this, &Widget::slotShowLabelCount);
//    // 延时1秒发射信号
//    QTimer::singleShot(1000, this, &Widget::slotShowLabelCount);
    startTimer(1000);       // timer ID = 1
    startTimer(3000);       // timer ID = 4
}

// 定时器事件
void Widget::timerEvent(QTimerEvent *event)
{
    qDebug() << "Timer ID = " << event->timerId();
}

Widget::~Widget()
{
    delete ui;
}
