#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <QWidget>
#include <QMouseEvent>
#include <QCloseEvent>

class MouseEvent : public QWidget{
public:
    explicit MouseEvent(QWidget *parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;

private:
    bool m_bPressed;
    QPoint m_point;
};

#endif // MOUSEEVENT_H
