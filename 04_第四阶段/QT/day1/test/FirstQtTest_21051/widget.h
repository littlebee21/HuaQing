#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT        // 一个宏,使用信号和槽的功能必须要依赖这个宏

public:
    // 使用场景: 用来修饰单形参的构造函数
    // 作用: 防止从该形参类型向该类类型隐式转化
    explicit Widget(QWidget *parent = nullptr);
    // 析构函数,用来释放资源
    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
