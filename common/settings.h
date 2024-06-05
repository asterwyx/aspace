#pragma once
#include <QObject>
#include <QVariant>
#include "settingsbackend.h"

class Settings : public QObject {
    Q_OBJECT
    Q_PROPERTY(SettingsBackend *backend READ backend WRITE setBackend)

public:

    static QPointer<Settings> applicationSettings();
    Settings(QObject *parent = nullptr);

    QVariant get(const QString &key) const;
    void set(const QString &key, const QVariant &value);
    void reset(const QString &key);
    bool hasKey(const QString &key);

    inline SettingsBackend *backend() { return m_backend; }
    inline void setBackend(SettingsBackend *backend) { m_backend = backend; }

private:
    SettingsBackend *m_backend;
};
