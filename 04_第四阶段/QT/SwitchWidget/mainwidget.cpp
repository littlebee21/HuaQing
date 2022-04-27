#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    m_pOne = new One;
    m_pTwo = new Two;
    m_pStackedLayout = new QStackedLayout(this);
    // 将one界面和two界面添加到StackedLayout中
    // 在这里已经确定了界面的层级关系(one在最上面)
    m_pStackedLayout->addWidget(m_pOne);
    m_pStackedLayout->addWidget(m_pTwo);

    connect(m_pOne, &One::display,
            m_pStackedLayout, &QStackedLayout::setCurrentIndex);
    connect(m_pTwo, &Two::display,
            m_pStackedLayout, &QStackedLayout::setCurrentIndex);
}

MainWidget::~MainWidget(){
    delete ui;
}

