#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QRect>
#include <QPoint>
#include "mainframe.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

     //设置鼠标按下可移动窗口的区域，在子窗口中必须设置该区域
    void setAreaMovable(const QRect areaPos);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::Widget *ui;
    bool m_bPressed;    //鼠标按下标志（不分左右键）
    QPoint m_posArea;
    QRect m_areaMovable;
    QWidget *m_pmainFrame;
};

#endif // WIDGET_H
