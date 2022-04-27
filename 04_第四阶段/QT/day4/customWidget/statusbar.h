#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>

namespace Ui {
class statusBar;
}

class statusBar : public QWidget
{
    Q_OBJECT

public:
    explicit statusBar(QWidget *parent = nullptr);
    ~statusBar();

private:
    Ui::statusBar *ui;
};

#endif // STATUSBAR_H
