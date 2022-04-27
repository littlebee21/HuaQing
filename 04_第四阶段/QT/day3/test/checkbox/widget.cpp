#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 开启互斥功能
    // ui->checkBox->setAutoExclusive(true);
    // ui->checkBox_2->setAutoExclusive(true);
    // 打开半选功能
    ui->checkBox->setTristate(true);

    connect(ui->checkBox, &QCheckBox::stateChanged, this, &Widget::slotChangeState);
}

void Widget::slotChangeState(int index)
{
    switch (index) {
    case Qt::Unchecked:
        ui->label->setText("Unchecked");
        break;
    case Qt::PartiallyChecked:
        ui->label->setText("PartiallyChecked");
        break;
    case Qt::Checked:
        ui->label->setText("Checked");
        break;
    default:
        break;
    }
}

Widget::~Widget()
{
    delete ui;
}
