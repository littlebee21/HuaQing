#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "titlebar.h"
#include "centerwidget.h"
#include "statusbar.h"
#include <QMouseEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::Widget *ui;
    titleBar *m_pTitlebar;
    centerWidget *m_pCenterWidget;
    statusBar *m_pStatusBar;

    QPoint m_point;     // 坐标点
    bool m_bPressed;    // 鼠标按下的标志
};

#endif // WIDGET_H
