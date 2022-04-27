#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "sonwidget.h"

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
    void slotCreateNewWidget();

private:
    Ui::Widget *ui;
    SonWidget *m_pSonWidget;
};

#endif // WIDGET_H
