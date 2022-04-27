#include "one.h"
#include "ui_one.h"

One::One(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::One)
{
    ui->setupUi(this);
    connect(ui->twoBtn, &QPushButton::clicked, this, &One::slotSwitchToWidgetTwo);
    connect(ui->threeBtn, &QPushButton::clicked, this, &One::slotSwitchToWidgetThree);
}

One::~One()
{
    delete ui;
}

void One::slotSwitchToWidgetTwo()
{
    emit display(1);
}

void One::slotSwitchToWidgetThree()
{
    emit display(2);
}
