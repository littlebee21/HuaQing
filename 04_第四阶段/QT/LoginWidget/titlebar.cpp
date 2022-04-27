#include "titlebar.h"
#include "ui_titlebar.h"
#include "commonhelper.h"
#include <QDebug>

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);
    connect(ui->closeBtn, &QAbstractButton::clicked,
            this, &TitleBar::slotCloseWidget);
    CommonHelper::setStyle("C:/Users/ciyeer/Desktop/LoginWidget/css/login.css");
}

void TitleBar::slotCloseWidget()
{
    this->parentWidget()->close();
    // exit(-1);
}

TitleBar::~TitleBar()
{
    delete ui;
}
