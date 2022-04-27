#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QDebug>
#include <QTimer>

LoginWidget::LoginWidget(MouseEvent *parent)
    : MouseEvent(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    // 无边框
    setWindowFlags(Qt::FramelessWindowHint);
    m_pTitleBar = new TitleBar;
    m_pCenterWidget = new CenterWidget;
    m_pStatusBar = new StatusBar;

    ui->hLayout_Title->addWidget(m_pTitleBar);
    ui->hLayout_Center->addWidget(m_pCenterWidget);
    ui->hLayout_Status->addWidget(m_pStatusBar);

    connect(m_pCenterWidget, &CenterWidget::singalSendMsgToStatus,
            m_pStatusBar, &StatusBar::slotRecieveWarningMsg);
    connect(m_pCenterWidget, &CenterWidget::singalSendMsgToStatus,
            m_pStatusBar, &StatusBar::slotRecieveHideFlag);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}
