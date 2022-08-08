#include "powerplugin.h"
#include "battery.h"
#include "powerplugin_p.h"

BEGIN_USER_NAMESPACE
PowerPlugin::PowerPlugin() : d_ptr(new PowerPluginPrivate(this)) {}

PowerPlugin::~PowerPlugin() = default;

QString PowerPlugin::pluginName() const { return {"dde-power"}; }

QString PowerPlugin::pluginDisplayName() const { return {"Power"}; }

QWidget *PowerPlugin::pluginWidget(const QString &key) {
    Q_UNUSED(key)
    auto battery = new Battery();
    battery->resize(400, 200);
    battery->setBorderRadius(3);
    battery->setBgRadius(3);
    battery->setAlarmValue(20);
    battery->setBorderColorStart(QColor(105, 105, 105));
    battery->setBorderColorEnd(QColor(40, 40, 40));
    battery->setNormalColorStart(QColor(0, 255, 0));
    battery->setNormalColorEnd(QColor(0, 170, 0));
    battery->setAlarmColorStart(QColor(255, 255, 0));
    battery->setAlarmColorEnd(QColor(255, 170, 0));
    battery->setMinValue(0);
    battery->setMaxValue(100);
    battery->setHeadRadius(2);
    battery->setValue(50);
    battery->setStep(0.1);
    return battery;
}

PowerPluginPrivate::PowerPluginPrivate(PowerPlugin *q) : q_ptr(q) {}

PowerPluginPrivate::~PowerPluginPrivate() = default;
END_USER_NAMESPACE