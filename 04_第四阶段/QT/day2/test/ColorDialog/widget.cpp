#include "widget.h"
#include "ui_widget.h"
#include <QColorDialog>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->colorBtn, &QPushButton::clicked, this, &Widget::slotOpenColorDialog);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotOpenColorDialog()
{
    QColorDialog::getColor(Qt::red);
    qDebug() << "color select";
}

