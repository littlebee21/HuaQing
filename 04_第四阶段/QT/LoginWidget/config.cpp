#include "config.h"
#include <QDebug>

Config::Config(QString strPath){
    m_pSettings = new QSettings(strPath, QSettings::IniFormat);
}

void Config::writeSettings(QString strNode, QString strKey, QVariant qvarvalue){
    m_pSettings->setValue(QString("/%1/%2").arg(strNode).arg(strKey), qvarvalue);
}

QVariant Config::readSettings(QString strNode, QString strKey){
    QVariant qvar = m_pSettings->value(QString("/%1/%2").arg(strNode).arg(strKey));
    return qvar;
}

Config::~Config(){
    delete m_pSettings;
    m_pSettings = nullptr;
}
