#include "mainwindow.h"
#include "aboutdialog.h"
#include <finddialog.h>
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
