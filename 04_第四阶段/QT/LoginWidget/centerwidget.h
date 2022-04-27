#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QSettings>
#include "config.h"

namespace Ui {
class CenterWidget;
}

class CenterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CenterWidget(QWidget *parent = nullptr);
    ~CenterWidget();

    // 初始化LineEdit属性
    void initLineEdit();

public slots:
    // 登录需要的槽函数(关联按钮)
    void slotLoginWidget();
    void slotSendMsgToStatusBar();

signals:
    // 传递参数给statusbar
    void singalSendMsgToStatus(QString msg);
    // 给statusBar触发定时器
    void signalSendTimeoutFlag();

private:
    int m_nCount;       // 输入密码的次数
    QString m_strUserName;
    QString m_strPasswd;
    QTimer *m_pTimerHideWarning;

    Config *m_pConfig;

    Ui::CenterWidget *ui;
};

#endif // CENTERWIDGET_H
