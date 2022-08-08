#pragma once
#include "weatherplugin.h"
BEGIN_USER_NAMESPACE
class WeatherPluginPrivate {
public:
    WeatherPluginPrivate(WeatherPlugin *q);
    ~WeatherPluginPrivate();
private:
    Q_DECLARE_PUBLIC(WeatherPlugin)
    WeatherPlugin *q_ptr;
};
END_USER_NAMESPACE