#include "wrapsettings.h"

WrapSettings g_wrapSettings;

WrapSettings::WrapSettings() : QSettings("Franticware", "defisheye")
{
}

void WrapSettings::setPluginName(const QString& s)
{
    pluginName = s;
}

void WrapSettings::saveDefault(const char* name, float f)
{
    setValue(fullKeyName(name), f);
    sync();
}

void WrapSettings::loadDefault(const char* name, float& f)
{
    sync();
    QString keyName = fullKeyName(name);
    if (contains(keyName))
    {
        QVariant val = value(keyName);

        bool ok;
        float tmp = val.toFloat(&ok);
        if (ok)
        {
            f = tmp;
        }
    }
}

void WrapSettings::factoryReset(const char* name)
{
    remove(fullKeyName(name));
    sync();
}

bool WrapSettings::exists(const char* name)
{
    return contains(fullKeyName(name));
}

QString WrapSettings::fullKeyName(const char* name)
{
    return pluginName + "/" + name;
}
