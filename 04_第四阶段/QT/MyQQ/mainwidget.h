#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTimer>
#include "titlebar.h"
#include "statusbar.h"
#include "centerwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget{
    Q_OBJECT
public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    TitleBar *m_pTitleBar;
    StatusBar *m_pStatusBar;
    CenterWidget *m_pCenterWidget;
    QTimer *m_pTimer;
};
#endif // MAINWIDGET_H
