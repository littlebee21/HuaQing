#include "centerwidget.h"
#include "ui_centerwidget.h"
#include <QDebug>
#include <QSettings>

CenterWidget::CenterWidget(QWidget *parent) :
    QWidget(parent),
    m_nCount(3),
    ui(new Ui::CenterWidget){
    ui->setupUi(this);
    m_pConfig = new Config("C:/Users/ciyeer/Desktop/LoginWidget/config.ini");
    m_strUserName = m_pConfig->readSettings("user", "name").toString();
    m_strPasswd = m_pConfig->readSettings("user", "password").toString();
//    Config("这是路径").readSettings("user", "password").toString();
    qDebug() << m_strUserName << "   " << m_strPasswd;

    initLineEdit();
    m_pTimerHideWarning = new QTimer(this);
    connect(m_pTimerHideWarning, &QTimer::timeout,
            this, &CenterWidget::slotSendMsgToStatusBar);
    connect(ui->loginBtn, &QAbstractButton::clicked,
            this, &CenterWidget::slotLoginWidget);
}

void CenterWidget::initLineEdit(){
    ui->nameLineEdit->setAlignment(Qt::AlignCenter);    // 居中
    ui->passwdlineEdit->setAlignment(Qt::AlignCenter);
    ui->nameLineEdit->setPlaceholderText("QQ号/手机号/邮箱");
    ui->passwdlineEdit->setPlaceholderText("密码");
    ui->passwdlineEdit->setEchoMode(QLineEdit::Password);
}

void CenterWidget::slotLoginWidget(){
    m_pTimerHideWarning->start(3000);
    if(m_nCount == 0)
        this->parentWidget()->close();
    if(ui->nameLineEdit->text().isEmpty()){
        emit singalSendMsgToStatus("用户名为空，请输入用户名");
        ui->passwdlineEdit->clear();
        return;
    }
    if(ui->passwdlineEdit->text().isEmpty()){
        emit singalSendMsgToStatus("密码为空，请输入密码");
        return;
    }

    if(ui->nameLineEdit->text() == m_strUserName){
        if(ui->passwdlineEdit->text() == m_strPasswd){
            emit singalSendMsgToStatus("登录成功");
        }
        else{
            m_nCount--;
            emit singalSendMsgToStatus(QString("密码错误，请重新输入密码, 还剩%1次机会").arg(m_nCount));
            ui->passwdlineEdit->clear();    // 清空密码框
        }
    }
    else{
        emit singalSendMsgToStatus("用户名错误，请重新输入账户名");
        ui->nameLineEdit->clear();
        ui->passwdlineEdit->clear();
    }
}

void CenterWidget::slotSendMsgToStatusBar(){
    emit singalSendMsgToStatus("");
}

CenterWidget::~CenterWidget(){
    delete ui;
    delete m_pTimerHideWarning;
    m_pTimerHideWarning = nullptr;
    delete m_pConfig;
    m_pConfig = nullptr;
}
