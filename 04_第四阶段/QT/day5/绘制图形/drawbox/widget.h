#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent*);

private:
    Ui::Widget *ui;
    QPainter *painter;
};

#endif // WIDGET_H
