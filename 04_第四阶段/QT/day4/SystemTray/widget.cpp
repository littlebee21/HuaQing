#include "widget.h"
#include "ui_widget.h"
#include <QIcon>
#include <QDebug>
#include "traymenu.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_pSystemTrayIcon = new QSystemTrayIcon(this);
    m_pSystemTrayIcon->setToolTip("这是我的托盘");
    m_pSystemTrayIcon->setIcon(QIcon(":/image/logo.ico"));
    m_pSystemTrayIcon->setVisible(true);    // 显示托盘

    TrayMenu *pTrayMenu = new TrayMenu(this);
    m_pSystemTrayIcon->setContextMenu(pTrayMenu);
    // connect(pTrayMenu, &TrayMenu::showWindow, this, &Widget::slotShowWindow);
    connect(pTrayMenu, &TrayMenu::showWindow, this, &Widget::slotCloseWindow);
}

void Widget::slotShowWindow()
{
    showNormal();
    raise();
    activateWindow();
}

void Widget::slotCloseWindow()
{
    qDebug() << "close";
    close();
}

Widget::~Widget()
{
    delete ui;
}
