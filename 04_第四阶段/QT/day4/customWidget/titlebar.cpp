#include "titlebar.h"
#include "ui_titlebar.h"
#include "common/commonhelper.h"

titleBar::titleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::titleBar)
{
    ui->setupUi(this);
    CommonHelper::setWindowStyle("C:/Users/cymer/Desktop/21051/QtTest/day4/customWidget/css/titleBar.css");
    connect(ui->closeBtn, &QPushButton::clicked, this, &titleBar::slotCloseWidget);
    connect(ui->miniBtn, &QPushButton::clicked, this, &titleBar::slotShowMinSize);
    connect(ui->maxBtn, &QPushButton::clicked, this, &titleBar::slotShowMaxSize);
}

void titleBar::slotCloseWidget()
{
    parentWidget()->close();            // 关闭父窗体
}

void titleBar::slotShowMaxSize()
{
    parentWidget()->showMaximized();    // 最大化父窗体
}

void titleBar::slotShowMinSize()
{
    parentWidget()->showMinimized();    // 最小化父窗体
}

void titleBar::slotShowRestoreSize()
{
    parentWidget()->showNormal();       // 还原父窗体
}

titleBar::~titleBar()
{
    delete ui;
}
