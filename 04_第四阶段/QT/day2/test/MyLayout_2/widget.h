#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>  // 竖直布局头文件
#include <QGridLayout>  // 网格布局

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
    QVBoxLayout *m_pVBoxLayout;
    QGridLayout *m_pGridLayout;
};

#endif // WIDGET_H
