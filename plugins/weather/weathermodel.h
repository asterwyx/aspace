#pragma once
#include "common_def.h"
#include "weatherdata.h"
#include "weatherinterface.h"
#include <QDBusConnection>


BEGIN_USER_NAMESPACE
class WeatherModel : public QObject {
    Q_OBJECT
public:
    WeatherModel(QObject *parent = nullptr);
    void updateCurrentWeather();
    CurrentWeather getCurrentWeather();

signals:
    void currentWeatherUpdated(CurrentWeather weather);

private:
    CurrentWeather      m_currentWeather;
    QDBusConnection     m_busConn;
    WeatherInterface    *m_weatherDBusInterface;
};

END_USER_NAMESPACE