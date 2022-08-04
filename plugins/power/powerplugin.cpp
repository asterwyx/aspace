#include "powerplugin.h"
#include "battery.h"
#include "powerplugin_p.h"

namespace dspace {
PowerPlugin::PowerPlugin(QWidget *parent)
    : PluginInterface(parent),
    d_ptr(new PowerPluginPrivate(this))
{}

PowerPlugin::~PowerPlugin() = default;

const QString PowerPlugin::pluginName() const {
    return QString("dde-power");
}

const QString PowerPlugin::pluginDisplayName() const {
    return QString("Power");
}

QWidget *PowerPlugin::pluginWidget(const QString &key) {
    Q_UNUSED(key)
    Q_D(PowerPlugin);
    return d->m_battery;
}

PowerPluginPrivate::PowerPluginPrivate(PowerPlugin *q)
    : q_ptr(q),
    m_battery(new Battery(q))
{}

PowerPluginPrivate::~PowerPluginPrivate() = default;
}