#include "settings.h"
#include "qgsettingsbackend.h"
#include <QString>
#include <QPointer>

static const QByteArray SchemaId = QByteArrayLiteral("net.asterwyx.aspace");
static const QByteArray Path = QByteArrayLiteral("/net/asterwyx/aspace/");

Settings::Settings(QObject *parent) : QObject(parent)
{
}

QPointer<Settings> Settings::applicationSettings()
{
    static Settings globalSettings;
    if (!globalSettings.backend()) {
        // 目前会按照一定的顺序去查找对应的后端，QGSettings的后端的优先级最高
        auto gsettings = new QGSettingsBackend(SchemaId, Path, &globalSettings);
        if (gsettings->valid())
            globalSettings.setBackend(gsettings);
    }
    return QPointer<Settings>(&globalSettings);
}

QVariant Settings::get(const QString &key) const
{
    if (!m_backend)
        return QVariant();
    return m_backend->get(key);
}

void Settings::set(const QString &key, const QVariant &value)
{
    if (!m_backend)
        return;
    m_backend->set(key, value);
}

void Settings::reset(const QString &key)
{
    if (!m_backend)
        return;
    m_backend->reset(key);
}

bool Settings::hasKey(const QString &key)
{
    if (!m_backend)
        return false;
    return m_backend->keys().contains(key);
}
