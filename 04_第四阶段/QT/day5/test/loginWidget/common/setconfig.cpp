#include "setconfig.h"

SetConfig::SetConfig(QString path)
{
    m_pSettings = new QSettings(path, QSettings::IniFormat);
}

SetConfig::~SetConfig()
{
    delete m_pSettings;
    m_pSettings = nullptr;
}

void SetConfig::writeToIniFile(QString strGroup, QString strKey, QString strValue)
{
    m_pSettings->beginGroup(strGroup);
    m_pSettings->setValue(strKey, strValue);
    m_pSettings->endGroup();
    m_pSettings->sync();        // 同步
}

QVariant SetConfig::readFromIniFile(QString strGroup, QString strKey)
{
    return m_pSettings->value(strGroup + "/" + strKey).toString();
}
