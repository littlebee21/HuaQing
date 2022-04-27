#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // radiobutton默认是打开互斥功能的
    // setAutoExclusive可以设置互斥功能,false取消互斥,true打开互斥(默认)
    // ui->radioButton->setAutoExclusive(false);
    // ui->radioButton_2->setAutoExclusive(false);

    connect(ui->radioButton, &QAbstractButton::toggled, this, &Widget::slotClickManbtn);
    connect(ui->radioButton_2, &QAbstractButton::toggled, this, &Widget::slotClickWomenbtn);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotClickManbtn()
{
    ui->label->setText(ui->radioButton->text());
}

void Widget::slotClickWomenbtn()
{
    ui->label->setText(ui->radioButton_2->text());
}
