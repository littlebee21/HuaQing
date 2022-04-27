#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMovie>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void slotShowTips();
    void slotClearTips();

private:
    Ui::Widget *ui;
    bool m_bFlag;
    QMovie *m_pMovie;
};
#endif // WIDGET_H
