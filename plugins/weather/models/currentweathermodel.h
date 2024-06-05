#pragma once
#include "common_def.h"
#include "weatherdata.h"
#include <QDBusConnection>


class CurrentWeatherModel : public QObject
{
    Q_OBJECT
public:
    explicit CurrentWeatherModel(QObject *parent = nullptr);
    ~CurrentWeatherModel() override;

    void setCurrentWeather(const CurrentWeather &weather);
    CurrentWeather getCurrentWeather();

signals:
    void currentWeatherChanged(const CurrentWeather &weather);

private:
    CurrentWeather m_currentWeather;
};
