#include "statusbar.h"
#include "ui_statusbar.h"

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar)
{
    ui->setupUi(this);
}

void StatusBar::slotClearWarningLabel(){
    ui->labelWarning->clear();
}

void StatusBar::slotShowWarningMsg(QString strMsg){
    ui->labelWarning->setText(strMsg);
}

StatusBar::~StatusBar(){
    delete ui;
}

