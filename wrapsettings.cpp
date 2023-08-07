#include "wrapsettings.h"

#include <QRegularExpression>

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

QString WrapSettings::getLensName() const
{
    QString base = pluginName.mid(0, pluginName.lastIndexOf('.'));
    int fIndex = base.lastIndexOf(QRegularExpression("[0-9]f[0-9]"));
    if (fIndex == -1)
    {
        return base;
    }
    QString fVal = base.mid(fIndex + 2);
    QString half = base.mid(0, fIndex + 1);
    int lastIndex = half.lastIndexOf(QRegularExpression("[^0-9.]"));
    if (lastIndex == -1)
    {
        return base;
    }
    ++lastIndex;
    QString brand = half.mid(0, lastIndex);
    QString focal = half.mid(lastIndex);

    if (brand.length() == 0)
    {
        return base;
    }
    brand[0] = brand[0].toUpper();
    return brand + " " + focal + "mm f/" + fVal;
}

QString WrapSettings::fullKeyName(const char* name)
{
    return pluginName + "/" + name;
}
