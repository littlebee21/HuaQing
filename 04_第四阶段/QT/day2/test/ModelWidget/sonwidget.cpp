#include "sonwidget.h"
#include "ui_sonwidget.h"

SonWidget::SonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SonWidget)
{
    ui->setupUi(this);
}

SonWidget::~SonWidget()
{
    delete ui;
}
