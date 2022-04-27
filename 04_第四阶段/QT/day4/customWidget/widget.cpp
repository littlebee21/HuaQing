#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_bPressed = false;
    // 去掉系统再带边框
    setWindowFlag(Qt::FramelessWindowHint);
    // 创建不同组件
    m_pTitlebar     = new titleBar;
    m_pCenterWidget = new centerWidget;
    m_pStatusBar    = new statusBar;
    // 把组件添加到界面布局中
    ui->verticalLayout_1->addWidget(m_pTitlebar);
    ui->verticalLayout_2->addWidget(m_pCenterWidget);
    ui->verticalLayout_3->addWidget(m_pStatusBar);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    // 移动当前窗口
    if (event->button() == Qt::LeftButton)      //判断左键是否按下
    {
        m_bPressed = true;          // 设置按下标志
        m_point = event->pos();     // 获取鼠标点击位置(在应用程序内的坐标)
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());       // 移动的距离
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)     // 去除声明但没使用的参数的宏(去警告)
    m_bPressed = false;
}


Widget::~Widget()
{
    delete ui;
}
