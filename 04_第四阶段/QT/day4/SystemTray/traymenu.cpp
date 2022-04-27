#include "traymenu.h"

TrayMenu::TrayMenu(QWidget *parent)
    : QMenu(parent)
{
    initActions();
    // connect(m_pActShow, &QAction::triggered, this, &TrayMenu::showWindow);
    connect(m_pActExit, &QAction::triggered, this, &TrayMenu::showWindow);
}

TrayMenu::~TrayMenu()
{

}

void TrayMenu::initActions()
{   
    // 创建菜单项
    m_pActShow      = new QAction(QStringLiteral("显示"), this);
    m_pActMiniSized = new QAction(QStringLiteral("最小化"), this);
    m_pActMaxSized  = new QAction(QStringLiteral("最大化"), this);
    m_pActRestored  = new QAction(QStringLiteral("还原"), this);
    m_pActSetting   = new QAction(QStringLiteral("设置"), this);
    m_pActAbout     = new QAction(QStringLiteral("关于"), this);
    m_pActExit      = new QAction(QStringLiteral("退出"), this);
    // 添加到上下文中
    this->addAction(m_pActShow);
    this->addAction(m_pActMiniSized);
    this->addAction(m_pActMaxSized);
    this->addAction(m_pActRestored);
    this->addAction(m_pActSetting);
    this->addAction(m_pActAbout);
    this->addAction(m_pActExit);
}
