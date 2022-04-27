#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>

namespace Ui {
class StatusBar;
}

class StatusBar : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar();

public slots:
    void slotClearWarningLabel();
    void slotShowWarningMsg(QString);

private:
    Ui::StatusBar *ui;
};

#endif // STATUSBAR_H
