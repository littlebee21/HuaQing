#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedLayout>
#include "one.h"
#include "two.h"
#include "three.h"

namespace Ui {
class Widget;
}

// 控制管理类(控制和管理所有界面的调整)
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QStackedLayout *m_pStackedLayout;
    One *m_pOne;
    Two *m_pTwo;
    Three *m_pThree;
};

#endif // WIDGET_H
