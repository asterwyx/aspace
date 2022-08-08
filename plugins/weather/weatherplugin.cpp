//
// Created by astrea on 8/2/22.
//

#include "weatherplugin.h"
#include "weatherplugin_p.h"
#include <QLabel>

BEGIN_USER_NAMESPACE

WeatherPlugin::WeatherPlugin() : d_ptr(new WeatherPluginPrivate(this)) {}
WeatherPlugin::~WeatherPlugin() = default;

QString WeatherPlugin::pluginName() const { return {"dde-weather"}; }
QString WeatherPlugin::pluginDisplayName() const { return {"Weather"}; }

QWidget *WeatherPlugin::pluginWidget(const QString &key) {
    Q_UNUSED(key)
    auto widget = new QLabel("<h1>Hello Weather</h1>");
    widget->setGeometry(0, 50, 300, 50);
    return widget;
}
WeatherPluginPrivate::WeatherPluginPrivate(WeatherPlugin *q) : q_ptr(q) {}

WeatherPluginPrivate::~WeatherPluginPrivate() = default;
END_USER_NAMESPACE