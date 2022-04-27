#include "widget.h"
#include <QApplication>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>

// 自定义消息处理函数
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n",
                localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n",
                localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n",
                localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n",
                localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n",
                localMsg.constData(), context.file, context.line, context.function);
        abort();
    default:
        break;
    }
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
    qFatal("This is a fatal message.");

    return a.exec();
}
