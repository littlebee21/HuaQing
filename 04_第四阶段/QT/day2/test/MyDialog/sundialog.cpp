#include "sundialog.h"
#include "ui_sundialog.h"

SunDialog::SunDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SunDialog)
{
    ui->setupUi(this);
}

SunDialog::~SunDialog()
{
    delete ui;
}
