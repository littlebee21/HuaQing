#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_pOne = new One;
    m_pTwo = new Two;
    m_pThree = new Three;
    m_pStackedLayout = new QStackedLayout(this);
    m_pStackedLayout->addWidget(m_pOne);        // one'index    ---   0
    m_pStackedLayout->addWidget(m_pTwo);        // two'index    ---   1
    m_pStackedLayout->addWidget(m_pThree);      // three'index  ---   2

    connect(m_pOne, &One::display, m_pStackedLayout, &QStackedLayout::setCurrentIndex);
    connect(m_pTwo, &Two::display, m_pStackedLayout, &QStackedLayout::setCurrentIndex);
    connect(m_pThree, &Three::display, m_pStackedLayout, &QStackedLayout::setCurrentIndex);
}

Widget::~Widget()
{
    delete ui;
    delete m_pStackedLayout;
    m_pStackedLayout = nullptr;
}
