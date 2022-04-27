#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

namespace Ui {
class titleBar;
}

class titleBar : public QWidget
{
    Q_OBJECT

public:
    explicit titleBar(QWidget *parent = nullptr);
    ~titleBar();

public slots:
    void slotCloseWidget();
    void slotShowMaxSize();
    void slotShowMinSize();
    void slotShowRestoreSize();

private:
    Ui::titleBar *ui;
};

#endif // TITLEBAR_H
