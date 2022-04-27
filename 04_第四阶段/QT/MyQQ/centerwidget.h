#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class CenterWidget;
}

class CenterWidget : public QWidget{
    Q_OBJECT
public:
    explicit CenterWidget(QWidget *parent = nullptr);
    ~CenterWidget();

signals:
    void signalSendMsgToStatusBar(QString strMsg);

public slots:
    void slotLoginWidget();
    void slotHideWarningLabel();

private:
    Ui::CenterWidget *ui;
    QString m_strUserName;
    QString m_strPassword;
    QTimer *m_pTimer;
};

#endif // CENTERWIDGET_H
