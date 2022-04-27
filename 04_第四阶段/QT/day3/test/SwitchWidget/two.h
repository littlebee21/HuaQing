#ifndef TWO_H
#define TWO_H

#include <QWidget>

namespace Ui {
class Two;
}

class Two : public QWidget
{
    Q_OBJECT

public:
    explicit Two(QWidget *parent = nullptr);
    ~Two();

signals:
    void display(int);

public slots:
    void slotSwitchToWidgetOne();
    void slotSwitchToWidgetThree();

private:
    Ui::Two *ui;
};

#endif // TWO_H
