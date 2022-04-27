#ifndef SONWIDGET_H
#define SONWIDGET_H

#include <QWidget>

namespace Ui {
class SonWidget;
}

class SonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SonWidget(QWidget *parent = nullptr);
    ~SonWidget();

private:
    Ui::SonWidget *ui;
};

#endif // SONWIDGET_H
