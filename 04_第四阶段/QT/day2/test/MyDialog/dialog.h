#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "sundialog.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
    void slotCreateNewDialog();

private:
    Ui::Dialog *ui;
    SunDialog *m_pSunDialog;
};

#endif // DIALOG_H
