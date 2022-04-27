#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <QApplication>
#include <QFile>
#include <QDebug>

class CommonHelper
{
public:
    static void setWindowStyle(QString strPath){
        QFile file(strPath);
        if(file.open(QFile::ReadOnly)){
            QString style = QLatin1String(file.readAll());
            // 注意: 这里的qApp是QApplication中的一个单例,用来全局访问QApplication中的方法
            qApp->setStyleSheet(style);
            file.close();
        }
        else
            qDebug() << "load qss file failed";
    }
};

#endif // COMMONHELPER_H
