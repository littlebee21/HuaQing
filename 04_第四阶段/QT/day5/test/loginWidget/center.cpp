#include "center.h"
#include "ui_center.h"

Center::Center(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Center)
{
    ui->setupUi(this);
    m_pLoginWidget = new LoginWidget;
    m_pMainWidget = new MainWidget;
    m_pStackedLayout = new QStackedLayout(this);
    m_pStackedLayout->addWidget(m_pLoginWidget);
    m_pStackedLayout->addWidget(m_pMainWidget);

    connect(m_pLoginWidget, &LoginWidget::display,
            m_pStackedLayout, &QStackedLayout::setCurrentIndex);
}

Center::~Center()
{
    delete ui;
}
