#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    m_bPressed(false),
    m_areaMovable(geometry()),
    m_pmainFrame(new mainFrame(this)),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//无边框
    ui->gridLayout_2->addWidget(m_pmainFrame);
    //setAttribute(Qt::WA_TranslucentBackground);//背景透明
}

Widget::~Widget()
{
    delete ui;
}
#if 0
void Widget::setAreaMovable(const QRect areaPos)
{
    if(m_areaMovable != areaPos)
        m_areaMovable = areaPos;
}
#endif
void Widget::mousePressEvent(QMouseEvent *e)
{
    // 鼠标左键
    if(e->button() == Qt::LeftButton)
        m_posArea = e->pos();
    m_bPressed = m_areaMovable.contains(m_posArea);
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bPressed)
        move(pos() + e->pos() - m_posArea);

}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
}
