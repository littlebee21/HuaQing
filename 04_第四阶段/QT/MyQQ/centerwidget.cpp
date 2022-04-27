#include "centerwidget.h"
#include "ui_centerwidget.h"

CenterWidget::CenterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CenterWidget)
{
    ui->setupUi(this);   

    // 去掉系统边框
    this->setWindowFlag(Qt::FramelessWindowHint);
    m_strUserName = "zhangsan";
    m_strPassword = "abc123";
    m_pTimer = new QTimer(this);
    // 居中对齐
    ui->lineEdit_username->setAlignment(Qt::AlignHCenter);
    ui->lineEdit_Passwd->setAlignment(Qt::AlignHCenter);
    // 设置占位标记提示
    ui->lineEdit_username->setPlaceholderText("Username");
    ui->lineEdit_Passwd->setPlaceholderText("Password");
    // 设置密码只写
    ui->lineEdit_Passwd->setEchoMode(QLineEdit::Password);

    connect(ui->loginBtn, &QAbstractButton::clicked,
            this, &CenterWidget::slotLoginWidget);
    connect(m_pTimer, &QTimer::timeout, this, &CenterWidget::slotHideWarningLabel);
}

void CenterWidget::slotLoginWidget(){
    if(ui->lineEdit_username->text().isEmpty()){
        emit signalSendMsgToStatusBar("username is empty!");
        ui->lineEdit_Passwd->clear();
//        m_pTimer->start(3000);  // 延时3s触发超时信号
        return;
    }
    if(ui->lineEdit_Passwd->text().isEmpty()){
        emit signalSendMsgToStatusBar("password is empty!");
//        m_pTimer->start(3000);  // 延时3s触发超时信号
        return;
    }
    if(!m_strUserName.compare(ui->lineEdit_username->text())){
        if(m_strPassword == ui->lineEdit_Passwd->text()){
            emit signalSendMsgToStatusBar("Login success!");
//            m_pTimer->start(3000);  // 延时3s触发超时信号
        }
        else{
            emit signalSendMsgToStatusBar("password error!");
            ui->lineEdit_Passwd->clear();
            m_pTimer->start(3000);  // 延时3s触发超时信号
        }
    }
    else{
        emit signalSendMsgToStatusBar("username is not exist!");
        ui->lineEdit_username->clear();
        ui->lineEdit_Passwd->clear();
//        m_pTimer->start(3000);  // 延时3s触发超时信号
    }
}

void CenterWidget::slotHideWarningLabel(){
    ui->label->clear();
}

CenterWidget::~CenterWidget(){
    delete ui;
}
