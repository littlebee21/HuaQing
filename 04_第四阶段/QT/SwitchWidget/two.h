#ifndef TWO_H
#define TWO_H

#include <QWidget>

namespace Ui {
class Two;
}

class Two : public QWidget{
    Q_OBJECT
public:
    explicit Two(QWidget *parent = nullptr);
    ~Two();

signals:
    void display(int);

public slots:
    void slotSwitchTwoToOne();

private:
    Ui::Two *ui;
};

#endif // TWO_H
