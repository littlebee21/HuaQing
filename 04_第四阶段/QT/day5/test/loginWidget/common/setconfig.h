#ifndef SETCONFIG_H
#define SETCONFIG_H

#include <QObject>
#include <QVariant>
#include <QSettings>

class SetConfig
{
public:
    SetConfig(QString path);
    ~SetConfig();
    // 将配置参数写入ini文件
    void writeToIniFile(QString strGroup, QString strKey, QString strValue);
    // 读取ini文件中的参数
    QVariant readFromIniFile(QString strGroup, QString strKey);

private:
    QSettings *m_pSettings;
};

#endif // SETCONFIG_H
