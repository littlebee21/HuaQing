#include "mainframe.h"
#include "ui_mainframe.h"

mainFrame::mainFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainFrame)
{
    ui->setupUi(this);
}

mainFrame::~mainFrame()
{
    delete ui;
}
