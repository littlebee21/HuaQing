#ifndef CONFIG_H
#define CONFIG_H
#include <QVariant>
#include <QSettings>

class Config
{
public:
    Config(QString strPath);
    ~Config();

    // 读写配置文件
    void writeSettings(QString strNode, QString strKey, QVariant qvarvalue);
    QVariant readSettings(QString strNode, QString strKey);

private:
    QString m_strConfigFilePath;
    QSettings *m_pSettings;
};

#endif // CONFIG_H
