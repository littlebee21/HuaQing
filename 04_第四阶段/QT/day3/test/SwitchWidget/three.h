#ifndef THREE_H
#define THREE_H

#include <QWidget>

namespace Ui {
class Three;
}

class Three : public QWidget
{
    Q_OBJECT

public:
    explicit Three(QWidget *parent = nullptr);
    ~Three();

signals:
    void display(int);

public slots:
    void slotSwitchToWidgetOne();
    void slotSwitchToWidgetTwo();

private:
    Ui::Three *ui;
};

#endif // THREE_H
