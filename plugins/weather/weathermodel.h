#pragma once
#include "common_def.h"
#include "weatherdata.h"
#include <QDBusConnection>


BEGIN_USER_NAMESPACE
class WeatherModel : public QObject {
    Q_OBJECT
public:
    WeatherModel(QObject *parent = nullptr);

    void setCurrentWeather(const CurrentWeather &weather);
    CurrentWeather getCurrentWeather();

signals:
    void currentWeatherChanged(CurrentWeather weather);

private:
    CurrentWeather      m_currentWeather;
};

END_USER_NAMESPACE