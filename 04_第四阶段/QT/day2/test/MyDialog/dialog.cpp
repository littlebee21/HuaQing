#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    // connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slotCreateNewDialog()));
    connect(ui->pushButton, &QPushButton::clicked, this, &Dialog::slotCreateNewDialog);

    // lambda表达式
    //    connect(ui->pushButton, &QPushButton::clicked, this, [](){
    //        qDebug() << "Hello world";
    //    });
}

void Dialog::slotCreateNewDialog()
{
    // dialog的非模式对话框
    // m_pSunDialog = new SunDialog;
    // m_pSunDialog->show();

    // dialog创建模式对话框的方法
    SunDialog dlg;  // 创建界面对象
    dlg.exec();     // 将创建的界面展示出来
}

Dialog::~Dialog()
{
    delete ui;
    // delete m_pSunDialog;
}
