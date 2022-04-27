#include "centerwidget.h"
#include "ui_centerwidget.h"

centerWidget::centerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::centerWidget)
{
    ui->setupUi(this);
}

centerWidget::~centerWidget()
{
    delete ui;
}
