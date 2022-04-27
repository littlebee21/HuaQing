#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>

namespace Ui {
class centerWidget;
}

class centerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit centerWidget(QWidget *parent = nullptr);
    ~centerWidget();

private:
    Ui::centerWidget *ui;
};

#endif // CENTERWIDGET_H
