#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QWidget>

namespace Ui {
    class mainFrame;
}

class mainFrame : public QWidget
{
    Q_OBJECT

public:
    explicit mainFrame(QWidget *parent = 0);
    ~mainFrame();

private:
    Ui::mainFrame *ui;
};

#endif // MAINFRAME_H
