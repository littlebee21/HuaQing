#include "two.h"
#include "ui_two.h"

Two::Two(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Two)
{
    ui->setupUi(this);
    connect(ui->oneBtn, &QPushButton::clicked, this, &Two::slotSwitchToWidgetOne);
    connect(ui->threeBtn, &QPushButton::clicked, this, &Two::slotSwitchToWidgetThree);
}

Two::~Two()
{
    delete ui;
}

void Two::slotSwitchToWidgetOne()
{
    emit display(0);
}

void Two::slotSwitchToWidgetThree()
{
    emit display(2);
}
