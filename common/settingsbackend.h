#pragma once
#include <QObject>

class SettingsBackend : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList keys READ keys)
public:
    SettingsBackend(QObject *parent = nullptr);
    virtual QVariant get(const QString &key) const = 0;
    virtual void set(const QString &key, const QVariant &value) = 0;
    virtual void reset(const QString &key) = 0;
    virtual bool valid() const = 0;
    virtual QStringList keys() { return {}; }
};
