#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void signalSendValue(int);

public slots:
    void slotBtnClicked();          // 响应按钮的槽----clicked
    void slotRecieveValue(int);     // 传递信号的槽----signalSendValue

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
