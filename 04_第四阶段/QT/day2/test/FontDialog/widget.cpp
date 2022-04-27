#include "widget.h"
#include "ui_widget.h"
#include <QFontDialog>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->fontBtn, &QPushButton::clicked, this, &Widget::slotOpenFontDialog);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotOpenFontDialog()
{
    bool ok;
    QFont font = QFontDialog::getFont(
                &ok, QFont("Helvetica [Cronyx]", 10), this);
    if (ok) {
        qDebug() << "Helvetica [Cronyx], 10";
    } else {
        qDebug() << "没被选中";
    }
}
