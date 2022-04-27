#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QTimer>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void danruinit();

private slots:
    void on_pushButton_2_clicked();
    void fadeOut();
    void fadeIn();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QGraphicsOpacityEffect *pEffect;
    float opacity = 0.0;
    QTimer timer1;
    QTimer timer2;
    bool m_bFlag;
};

#endif // WIDGET_H
