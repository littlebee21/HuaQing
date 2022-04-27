#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);    // 去边框
    m_pLineEdit = new QLineEdit(this);
    m_pLineEdit->setGeometry(200, 200, 350, 50);     // 设置组件的位置和大小的方法
    QFont font;
    font.setFamily(QString::fromUtf8("Arial"));
    font.setPointSize(14);
    font.setBold(true);
    font.setWeight(75);
    m_pLineEdit->setFont(font);
    m_pLineEdit->setAlignment(Qt::AlignHCenter);    // 设置位置(居中)
    //m_pLineEdit->setText("你好,世界");
    m_pLineEdit->setToolTip("这是输入框");       // 提示标签
    m_pLineEdit->setCursor(Qt::CrossCursor);   // 设置鼠标在组件上的形状
    m_pLineEdit->setFrame(false);              // 设置平台风格的开关
    // m_pLineEdit->clear();       // 清空
    // m_pLineEdit->setReadOnly(true);        // 设置只读模式
    // m_pLineEdit->setDisabled(true);        // 设置禁止模式
    m_pLineEdit->setPlaceholderText("请输入密码");   // 设置提示文字
    // Normal: 正常模式
    // NoEcho: 看不到文本(Linux密码输入就采用这种模式)
    // Password: 只能看到小黑点
    // PasswordEchoOnEdit: 编辑时正常显示,失去焦点以后变为密码模式(小黑点)
    m_pLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);              // 设置密码模式
}

Widget::~Widget()
{
    delete ui;
}
