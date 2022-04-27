#ifndef TRAYMENU_H
#define TRAYMENU_H

#include <QWidget>
#include <QMenu>
#include <QAction>

class TrayMenu : public QMenu
{
    Q_OBJECT    // 使用信号和槽必须得加这个
public:
    explicit TrayMenu(QWidget *parent = nullptr);
    ~TrayMenu();

    void initActions();

signals:
    void showWindow();

private:
    QAction *m_pActShow;
    QAction *m_pActExit;
    QAction *m_pActMiniSized;
    QAction *m_pActMaxSized;
    QAction *m_pActRestored;
    QAction *m_pActSetting;
    QAction *m_pActAbout;
    QAction *m_pActOpenMainPanel;
};

#endif // TRAYMENU_H
