#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;       // 创建一个界面对象
    w.show();       // 通过show的方法将界面展示出来

    return a.exec();
}
