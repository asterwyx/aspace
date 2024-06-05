#pragma once
#include "settingsbackend.h"
#include <qgsettings.h>



class QGSettingsBackend : public SettingsBackend {
public:
    QGSettingsBackend(const QByteArray &schemaId, const QByteArray &path = QByteArray(), QObject *parent = nullptr);

    QVariant get(const QString &key) const override;
    void set(const QString &key, const QVariant &value) override;
    void reset(const QString &key) override;
    QStringList keys() override;
    bool valid() const override;

private:
    QGSettings *m_nativeContext;
};
