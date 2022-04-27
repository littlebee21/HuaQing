#include "three.h"
#include "ui_three.h"

Three::Three(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Three)
{
    ui->setupUi(this);
    connect(ui->oneBtn, &QPushButton::clicked, this, &Three::slotSwitchToWidgetOne);
    connect(ui->twoBtn, &QPushButton::clicked, this, &Three::slotSwitchToWidgetTwo);
}

Three::~Three()
{
    delete ui;
}

void Three::slotSwitchToWidgetOne()
{
    emit display(0);
}

void Three::slotSwitchToWidgetTwo()
{
    emit display(1);
}
