#ifndef CENTER_H
#define CENTER_H

#include <QWidget>
#include <QStackedLayout>
#include "loginwidget.h"
#include "mainwidget.h"

namespace Ui {
class Center;
}

class Center : public QWidget
{
    Q_OBJECT

public:
    explicit Center(QWidget *parent = nullptr);
    ~Center();

private:
    Ui::Center *ui;
    LoginWidget *m_pLoginWidget;
    MainWidget *m_pMainWidget;

    QStackedLayout *m_pStackedLayout;
};

#endif // CENTER_H
