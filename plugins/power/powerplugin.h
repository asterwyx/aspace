#pragma once
#include "plugininterface.h"
#include <QScopedPointer>
#include <QWidget>

namespace dspace {
class PowerPluginPrivate;
class PowerPlugin : public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_INTERFACE_ID)
    Q_INTERFACES(PluginInterface)

public:
    explicit PowerPlugin(QWidget *parent = nullptr);
    ~PowerPlugin() override;
    const QString pluginName() const override;
    const QString pluginDisplayName() const override;
    QWidget *pluginWidget(const QString &key) override;

private:
    Q_DECLARE_PRIVATE(PowerPlugin)
    QScopedPointer<PowerPluginPrivate> d_ptr;
};
}
