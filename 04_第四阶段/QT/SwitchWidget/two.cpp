#include "two.h"
#include "ui_two.h"

Two::Two(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Two)
{
    ui->setupUi(this);
    connect(ui->oneBtn, &QPushButton::clicked,
            this, &Two::slotSwitchTwoToOne);
}

void Two::slotSwitchTwoToOne(){
    emit display(0);
}

Two::~Two(){
    delete ui;
}


