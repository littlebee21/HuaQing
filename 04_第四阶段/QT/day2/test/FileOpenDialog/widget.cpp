#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->openBtn, &QPushButton::clicked, this, &Widget::slotOpenFile);
    connect(ui->saveAsBtn, &QPushButton::clicked, this, &Widget::slotSaveAsFile);
}

void Widget::slotOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open txt"), "C:/Users/cymer/Desktop/", tr("Txt Files (*.txt)"));
    qDebug() << fileName;
}

void Widget::slotSaveAsFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                 "C:/Users/cymer/Desktop/untitled.png",
                                 tr("Images (*.png)"));
    qDebug() << fileName;
}

Widget::~Widget()
{
    delete ui;
}
