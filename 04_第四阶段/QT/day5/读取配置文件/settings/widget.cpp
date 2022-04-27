#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QString qstrname = config().Get("user","name").toString();
    qDebug() << qstrname;
    QString qstrpasswd = config().Get("user","password").toString();
    qDebug() << qstrpasswd;
    int nport = config().Get("test","port").toInt();
    qDebug() << nport;
}

Widget::~Widget()
{
    delete ui;
}
