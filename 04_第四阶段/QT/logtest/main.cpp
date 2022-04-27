#include <QApplication>
#include <QDebug>
#include <cstdlib>
#include <cstdio>
#include <QMutex>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

// 自定义消息处理函数
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    // 加锁
    static QMutex mutex;
    mutex.lock();
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:    // 一旦执行到这里,程序自动结束
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }

    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString strMessage = QString("Message:%1 File:%2  Line:%3  Function:%4  DateTime:%5")
            .arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function).arg(strDateTime);

    // 将每天的日期作为日志文件的名字
    QString fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd") + ".txt";
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Append))
        return;
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
    file.close();

    // 解锁
    mutex.unlock();
}

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    // 安装消息处理函数
    qInstallMessageHandler(myMessageOutput);
    // 打印信息
    qDebug("This is a debug message.");
    qInfo("This is a info message.");
    qWarning("This is a warning message.");
    qCritical("This is a critical message.");
    qFatal("This is a fatal message.");
    return a.exec();
}
