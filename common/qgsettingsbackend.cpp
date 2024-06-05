#include "qgsettingsbackend.h"
#include <QVariant>

QGSettingsBackend::QGSettingsBackend(const QByteArray &schemaId, const QByteArray &path, QObject *parent)
    : SettingsBackend(parent)
{
    if (QGSettings::isSchemaInstalled(schemaId))
        m_nativeContext = new QGSettings(schemaId, path, this);
    else
        m_nativeContext = nullptr;
}

QVariant QGSettingsBackend::get(const QString &key) const
{
    if (!valid())
        return QVariant();
    return m_nativeContext->get(key);
}

void QGSettingsBackend::set(const QString &key, const QVariant &value)
{
    if (!valid())
        return;
    m_nativeContext->set(key, value);
}

void QGSettingsBackend::reset(const QString &key)
{
    if (!valid())
        return;
    m_nativeContext->reset(key);
}

QStringList QGSettingsBackend::keys()
{
    if (!valid())
        return SettingsBackend::keys();
    return m_nativeContext->keys();
}

bool QGSettingsBackend::valid() const
{
    return m_nativeContext != nullptr;
}
