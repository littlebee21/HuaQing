#include "one.h"
#include "ui_one.h"

One::One(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::One)
{
    ui->setupUi(this);
    connect(ui->twoBtn, &QPushButton::clicked,
            this, &One::slotSwitchOneToTwo);
}

void One::slotSwitchOneToTwo(){
    emit display(1);
}

One::~One(){
    delete ui;
}
