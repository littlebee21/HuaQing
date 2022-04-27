#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMovie>

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
    void slotStartOrStopMovie();

private:
    Ui::Widget *ui;
    QMovie *m_pMovie;
    bool m_bMovieState;
};

#endif // WIDGET_H
