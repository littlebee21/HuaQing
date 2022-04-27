#include "statusbar.h"
#include "ui_statusbar.h"
#include <QDebug>

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar)
{
    ui->setupUi(this);
}

void StatusBar::slotRecieveWarningMsg(QString strMsg)
{
    ui->labelWarning->setText(strMsg);
}

void StatusBar::slotRecieveHideFlag(QString)
{
    //ui->labelWarning->clear();
}

StatusBar::~StatusBar()
{
    delete ui;
}
