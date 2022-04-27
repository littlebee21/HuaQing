#include "widget.h"
#include "ui_widget.h"
#include <QMenu>
#include <QAction>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QMenu *pMenu = new QMenu;

    QAction *actOpen = new QAction("打开");
    QAction *actClose = new QAction("关闭");
    QAction *actExit = new QAction("退出");
    QAction *actRestart = new QAction("重启");
    actOpen->setStatusTip("Open");

    pMenu->addAction(actOpen);
    pMenu->addAction(actClose);
    pMenu->addAction(actExit);
    pMenu->addAction(actRestart);

    ui->menuBtn->setMenu(pMenu);

    connect(actClose, &QAction::triggered, this, &QWidget::close);
}

Widget::~Widget()
{
    delete ui;
}
