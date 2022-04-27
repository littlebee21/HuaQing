#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "mouseevent.h"
#include "titlebar.h"
#include "centerwidget.h"
#include "statusbar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public MouseEvent
{
    Q_OBJECT

public:
    LoginWidget(MouseEvent *parent = nullptr);
    ~LoginWidget();

private:
    Ui::LoginWidget *ui;

    TitleBar *m_pTitleBar;
    CenterWidget *m_pCenterWidget;
    StatusBar *m_pStatusBar;
};
#endif // LOGINWIDGET_H
