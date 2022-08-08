#pragma once

#include <QObject>
#include <QList>
#include <QPair>

#include "namespace.h"

BEGIN_USER_NAMESPACE
class WeatherPrivate;
class Weather : public QObject
{
    Q_OBJECT
public:
    enum TemperatureUnit {
        CELSIUS,
        FAHRENHEIT
    };
    enum WeatherOverview {
        SUNNY,
        RAINY,
        CLOUDY,
        WINDY,
        SUNNY2RAINY,
        SUNNY2CLOUDY,
        CLOUDY2SUNNY,
        RAINY2SUNNY
    };
    explicit Weather(QObject *parent = nullptr);
    ~Weather();
    int                                             getCurrentTemperature();
    TemperatureUnit                                 getCurrentTemperatureUnit();
    WeatherOverview                                 getCurrentWeather();
    QList<QPair<WeatherOverview, QPair<int, int>>>  getNextFifteenDaysWeather();

signals:
    void weatherChanged(Weather::WeatherOverview current);
    void temperatureChanged(int currentTemperature);


public slots:
    void setTemperatureUnit(Weather::TemperatureUnit unit);

private:
    Q_DECLARE_PRIVATE(Weather)
    WeatherPrivate *d_ptr;
};
END_USER_NAMESPACE
