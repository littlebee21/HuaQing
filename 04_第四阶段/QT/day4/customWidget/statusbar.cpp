#include "statusbar.h"
#include "ui_statusbar.h"

statusBar::statusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statusBar)
{
    ui->setupUi(this);
}

statusBar::~statusBar()
{
    delete ui;
}
