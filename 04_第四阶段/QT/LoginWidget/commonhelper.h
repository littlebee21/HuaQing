#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <QApplication>
#include <QFile>
#include <QDebug>

class CommonHelper{
public:
    static void setStyle(QString strPath){
        QFile file(strPath);
        if(!file.open(QFile::ReadOnly)){
            qDebug() << "Open css file failed!";
            return;
        }
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();
    }
};

#endif // COMMONHELPER_H
