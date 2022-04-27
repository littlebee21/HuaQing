#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "common/setconfig.h"
#include <QDebug>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    connect(ui->LoginBtn, &QPushButton::clicked, this, &LoginWidget::slotLogin);
}

/*登录按钮*/
void LoginWidget::slotLogin()
{
    // 这里的路径可以改为相对路径
    SetConfig config("C:/Users/cymer/Desktop/21051/QtTest/day5/loginWidget/config.ini");
    // config.writeToIniFile("Login", "username", "Zhangsan");
    // config.writeToIniFile("Login", "password", "abc123");

    if(ui->usrname->text() == config.readFromIniFile("Login", "username"))
    {
        if(ui->password->text() == config.readFromIniFile("Login", "password")){
            emit display(1);
        }
        else if(ui->password->text() == ""){
            qDebug() << "密码为空,请输入密码";
        }
        else {
            qDebug() << "密码输入错误,请重新输入";
            ui->password->clear();
        }
    }
    else if(ui->usrname->text() == ""){
        qDebug() << "用户名为空,请输入用户名";
        ui->usrname->clear();
        ui->password->clear();
    }
    else {
        qDebug() << "用户名输入错误,请重新输入";
        ui->usrname->clear();
        ui->password->clear();
    }
}

LoginWidget::~LoginWidget()
{
    delete ui;
}
