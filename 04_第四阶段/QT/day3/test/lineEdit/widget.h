#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QLineEdit *m_pLineEdit;
};

#endif // WIDGET_H
