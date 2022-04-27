#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->openBtn, &QPushButton::clicked, this, &Widget::slotOpenMessageBoxDialog);
    connect(ui->openBtn_2, &QPushButton::clicked, this, &Widget::slotOpenMessageBoxWarning);
    connect(ui->quesBtn, &QPushButton::clicked, this, &Widget::slotOpenMessageBoxQues);
    connect(ui->infoBtn, &QPushButton::clicked, this, &Widget::slotOpenMessageBoxInfo);
    connect(ui->criticalBtn, &QPushButton::clicked, this, &Widget::slotOpenMessageBoxCritical);

    connect(ui->aboutBtn, &QPushButton::clicked, this, &Widget::slotOpenAboutDialog);
    connect(ui->aboutQtBtn, &QPushButton::clicked, this, &Widget::slotOpenAboutQtDialog);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotOpenMessageBoxDialog()
{
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
}

void Widget::slotOpenMessageBoxWarning()
{
    int ret = QMessageBox::warning(this, tr("Office"),
                                   tr("The document has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save
                                   | QMessageBox::Discard
                                   | QMessageBox::Cancel,
                                   QMessageBox::Save);
}

void Widget::slotOpenMessageBoxQues()
{
    int ret = QMessageBox::question(this, tr("Office"),
                                    tr("The document has been modified.\n"
                                       "Do you want to save your changes?"),
                                    QMessageBox::Save
                                    | QMessageBox::Discard
                                    | QMessageBox::Cancel,
                                    QMessageBox::Save);
}

void Widget::slotOpenMessageBoxCritical()
{
    int ret = QMessageBox::critical(this, tr("Office"),
                                    tr("The document has been modified.\n"
                                       "Do you want to save your changes?"),
                                    QMessageBox::Save
                                    | QMessageBox::Discard
                                    | QMessageBox::Cancel,
                                    QMessageBox::Save);
}

void Widget::slotOpenMessageBoxInfo()
{
    int ret = QMessageBox::information(this, tr("Office"),
                                       tr("The document has been modified.\n"
                                          "Do you want to save your changes?"),
                                       QMessageBox::Save
                                       | QMessageBox::Discard
                                       | QMessageBox::Cancel,
                                       QMessageBox::Save);
    switch (ret) {
    case QMessageBox::Save:
        qDebug() << "Save";
        break;
    case QMessageBox::Discard:
        qDebug() << "Discard";
        break;
    case QMessageBox::Cancel:
        qDebug() << "Cancel";
        break;
    default:
        qDebug() << "error";
        break;
    }
}

void Widget::slotOpenAboutDialog()
{
    QMessageBox::about(this, "关于",
                       "Fault tolerant heap shim applied to current process. "
                       "This is usually due to previous crashes. ***");
}

void Widget::slotOpenAboutQtDialog()
{
    QMessageBox::aboutQt(this, "关于Qt");
}


