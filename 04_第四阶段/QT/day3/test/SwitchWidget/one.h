#ifndef ONE_H
#define ONE_H

#include <QWidget>

namespace Ui {
class One;
}

class One : public QWidget
{
    Q_OBJECT

public:
    explicit One(QWidget *parent = nullptr);
    ~One();

signals:
    void display(int);

public slots:
    void slotSwitchToWidgetTwo();
    void slotSwitchToWidgetThree();

private:
    Ui::One *ui;
};

#endif // ONE_H
