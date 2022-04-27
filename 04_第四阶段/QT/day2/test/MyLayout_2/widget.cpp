#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_pVBoxLayout = new QVBoxLayout;
    // 注意pushbutton添加顺序, 第一个添加在上面
    m_pVBoxLayout->addWidget(ui->pushButton_1);
    m_pVBoxLayout->addWidget(ui->pushButton_2);
    m_pVBoxLayout->addWidget(ui->pushButton_3);
    m_pVBoxLayout->addWidget(ui->pushButton_4);
    m_pVBoxLayout->addWidget(ui->pushButton_5);

    m_pGridLayout = new QGridLayout(this);
    // 网格布局 , 0, 0表示网格中的0行0列
    m_pGridLayout->addLayout(m_pVBoxLayout, 0, 0);
}

Widget::~Widget()
{
    delete ui;
    // delete m_pVBoxLayout;   // 在这里其实不需要delete,因为设置的父窗体是QWidget,继承自QObject
    // m_pVBoxLayout = nullptr;
}
