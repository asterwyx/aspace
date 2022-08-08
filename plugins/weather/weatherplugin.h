#pragma once
#include "plugininterface.h"
#include <QWidget>
#include <QScopedPointer>
#include "namespace.h"

BEGIN_USER_NAMESPACE
class WeatherPluginPrivate;
class WeatherPlugin : public QObject, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_INTERFACE_ID)
    Q_INTERFACES(PluginInterface)
public:
    WeatherPlugin();
    ~WeatherPlugin() override;
    QString pluginName() const override;
    QString pluginDisplayName() const override;
    QWidget *pluginWidget(const QString &key) override;
private:
    Q_DECLARE_PRIVATE(WeatherPlugin)
    QScopedPointer<WeatherPluginPrivate> d_ptr;
};

END_USER_NAMESPACE

