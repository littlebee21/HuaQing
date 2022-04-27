#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

signals:    // 这是自定义信号的方法
    /*
     *  信号的特点: 只有声明,没有函数体
     *  信号还可以带参数
     */
    void signalClickeSend();      // 在这里,这个信号暂时不用,因为QAbstractButton自带信号

public slots:   // 声明槽的方法(自定义)
    /*
     *  槽的特点: 几乎和普通成员函数一致
     *  可以带参数
     *  不同点: 声明时,需要在访问权限后面添加slots
     */
    void slotPrintText();
    void slotPrintText2();

    void slotConcernAnotherSignal();

private:
    Ui::Widget *ui;
    int m_nCounter;
};

#endif // WIDGET_H
