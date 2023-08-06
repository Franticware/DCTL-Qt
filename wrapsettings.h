#ifndef WRAPSETTINGS_H
#define WRAPSETTINGS_H

#include <QSettings>
#include <QString>

class WrapSettings : public QSettings
{
public:
    WrapSettings();
    void setPluginName(const QString& s);
    void saveDefault(const char* name, float value);
    void loadDefault(const char* name, float& value);
    void factoryReset(const char* name);
    bool exists(const char* name);
    QString getLensName() const;

private:
    QString pluginName;

    QString fullKeyName(const char* name);
};

extern WrapSettings g_wrapSettings;

#endif // WRAPSETTINGS_H
