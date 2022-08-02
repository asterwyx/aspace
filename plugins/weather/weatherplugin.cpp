//
// Created by astrea on 8/2/22.
//

#include "weatherplugin.h"
#include "weatherplugin_p.h"
#include <QLabel>

namespace dspace {

WeatherPlugin::WeatherPlugin(QWidget *parent)
    : QWidget(parent), d_ptr(new WeatherPluginPrivate(this))
{

}
WeatherPlugin::~WeatherPlugin() {}

const QString WeatherPlugin::pluginName() const
{
    return QString("dde-weather");
}
const QString WeatherPlugin::pluginDisplayName() const {
    return QString("Weather");
}

QWidget *WeatherPlugin::pluginWidget(const QString &key) {
    auto widget = new QLabel("<h1>Hello Weather</h1>");
    widget->setGeometry(0, 50, 300, 50);
    return widget;
}
WeatherPluginPrivate::WeatherPluginPrivate(WeatherPlugin *q) : q_ptr(q) {}

WeatherPluginPrivate::~WeatherPluginPrivate() = default;
} // dspace