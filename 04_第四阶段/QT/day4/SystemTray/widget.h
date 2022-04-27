#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void slotShowWindow();
    void slotCloseWindow();

private:
    Ui::Widget *ui;
    QSystemTrayIcon *m_pSystemTrayIcon;
};

#endif // WIDGET_H
