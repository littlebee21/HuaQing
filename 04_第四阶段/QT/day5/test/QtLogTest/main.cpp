#include "widget.h"
#include <QApplication>
#include <QMutex>
#include <QTime>
#include <QFile>
#include <QTextStream>

// 自定义消息处理函数
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁
    static QMutex mutex;
    mutex.lock();

    QByteArray localMsg = msg.toLocal8Bit();

    QString strMsg;
    switch(type)
    {
    case QtDebugMsg:
        strMsg = QString("Debug:");
        break;
    case QtInfoMsg:
        strMsg = QString("Info:");
        break;
    case QtWarningMsg:
        strMsg = QString("Warning:");
        break;
    case QtCriticalMsg:
        strMsg = QString("Critical:");
        break;
    case QtFatalMsg:
        strMsg = QString("Fatal:");
        break;
    }

    // 设置输出信息格式
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString strMessage = QString("Message:%1 File:%2 Line:%3 Function:%4 DateTime:%5")
            .arg(localMsg.constData())
            .arg(context.file)
            .arg(context.line)
            .arg(context.function)
            .arg(strDateTime);

    // 创建文件
    QFile file("log.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Append))
        return;
    QTextStream stream(&file);
    stream << strMessage << "\n\r";
    file.flush();
    file.close();

    mutex.unlock();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //  安装消息处理程序
    qInstallMessageHandler(myMessageOutput);

    // 打印信息
    qDebug("This is a debug message.");
    qInfo("This is a info message.");
    qWarning("This is a warning message.");
    qCritical("This is a critical message.");
    qFatal("This is a fatal message.");     // 致命错误

    return a.exec();
}
