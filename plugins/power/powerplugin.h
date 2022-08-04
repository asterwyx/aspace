#pragma once
#include "plugininterface.h"
#include <QScopedPointer>
#include <QWidget>

namespace dspace {
class PowerPluginPrivate;
class PowerPlugin : public QObject, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_INTERFACE_ID)
    Q_INTERFACES(PluginInterface)

public:
    PowerPlugin();
    ~PowerPlugin() override;
    QString pluginName() const override;
    QString pluginDisplayName() const override;
    QWidget *pluginWidget(const QString &key) override;

private:
    Q_DECLARE_PRIVATE(PowerPlugin)
    QScopedPointer<PowerPluginPrivate> d_ptr;
};
}
