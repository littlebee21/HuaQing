#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // 支持高分屏按比例缩放
    // 如果电脑是高分屏(2K)电脑,则需要添加这行代码
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
