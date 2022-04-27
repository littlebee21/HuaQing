#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTimerEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    virtual void timerEvent(QTimerEvent *event) override;

public slots:
    void slotBtnClicked();
    void slotCloseWidget();
    void slotShowLabelCount();

private:
    Ui::Widget *ui;
    QTimer *m_pTimer;
    int m_nCount = 3;
};

#endif // WIDGET_H
