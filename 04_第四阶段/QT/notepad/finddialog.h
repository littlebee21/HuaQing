#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QFocusEvent>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog{
    Q_OBJECT
public:
    explicit FindDialog(QWidget *parent = nullptr);
    ~FindDialog();

signals:
    void signalFind(QString, bool);

public slots:
    // 查找内容
    void slotFindContent();
    void slotContentChanged();

protected:
    virtual void focusInEvent(QFocusEvent *event) override;
    // virtual void focusOutEvent(QFocusEvent *event) override;

private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
