#include "widget.h"
#include "ui_widget.h"
#include <QMovie>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_bMovieState(true)
{
    ui->setupUi(this);
    ui->pushButton->setText("暂停");
    m_pMovie = new QMovie(":/image/123.gif");
    m_pMovie->setSpeed(1000);
    ui->label->setMovie(m_pMovie);
    m_pMovie->start();
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::slotStartOrStopMovie);
}

void Widget::slotStartOrStopMovie()
{
    if(!m_bMovieState)
        ui->pushButton->setText("暂停");
    else {
        ui->pushButton->setText("开始");
    }
    m_pMovie->setPaused(m_bMovieState);
    m_bMovieState = !m_bMovieState;
}

Widget::~Widget()
{
    delete ui;
    delete m_pMovie;
    m_pMovie = nullptr;
}
