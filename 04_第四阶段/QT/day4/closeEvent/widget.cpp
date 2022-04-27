#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

void Widget::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::information(this, tr("My Application"),
                                    tr("是否关闭窗口?"),
                                    QMessageBox::Yes | QMessageBox::No,
                                    QMessageBox::Yes);
    switch (ret) {
    case QMessageBox::Yes:
        event->accept();    // 接受关闭请求(关闭)
        break;
    case QMessageBox::No:
        event->ignore();    // 忽略关闭请求(忽略关闭)
        break;
    default:
        break;
    }
}

Widget::~Widget()
{
    delete ui;
}
