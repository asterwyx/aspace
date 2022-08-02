#pragma once
#include "weatherplugin.h"
namespace dspace {
class WeatherPluginPrivate {
public:
    WeatherPluginPrivate(WeatherPlugin *q);
    ~WeatherPluginPrivate();
private:
    Q_DECLARE_PUBLIC(WeatherPlugin)
    WeatherPlugin *q_ptr;
};
}