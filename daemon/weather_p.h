#pragma once
#include "weather.h"

BEGIN_USER_NAMESPACE
class WeatherPrivate {
public:
    explicit WeatherPrivate(Weather *q);

private:
    Q_DECLARE_PUBLIC(Weather)
    Weather                     *q_ptr;
    Weather::TemperatureUnit    m_unit;
    int                         m_currentTemperature;
};


END_USER_NAMESPACE
