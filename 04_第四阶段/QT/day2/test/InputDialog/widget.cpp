#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QInputDialog>
#include <QDir>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->inputBtn, &QPushButton::clicked, this, &Widget::slotOpenInputDialog);
}

void Widget::slotOpenInputDialog()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         ui->inputBtn->text(), &ok);
    if (ok && !text.isEmpty())
        ui->textLabel->setText(text);
}

Widget::~Widget()
{
    delete ui;
}
