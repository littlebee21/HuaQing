#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    m_pTitleBar = new TitleBar;
    m_pStatusBar = new StatusBar;
    m_pCenterWidget = new CenterWidget;

    ui->titleBarLayout->addWidget(m_pTitleBar);
    ui->centerLayout->addWidget(m_pCenterWidget);
    ui->statusbarLayout->addWidget(m_pStatusBar);

    m_pTimer = new QTimer(this);

    connect(m_pCenterWidget, &CenterWidget::signalSendMsgToStatusBar,
            m_pStatusBar, &StatusBar::slotShowWarningMsg);
    // connect(m_pTimer, &QTimer::timeout, m_pStatusBar, &StatusBar::slotClearWarningLabel);
}

MainWidget::~MainWidget(){
    delete ui;
    delete m_pTimer;
    m_pTimer = nullptr;
}

