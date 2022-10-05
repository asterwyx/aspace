// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "weatherdata.h"
#include "enumdbus.h"
#include <QDBusMetaType>

BEGIN_USER_NAMESPACE
void Location::registerMetaTypes()
{
    qRegisterMetaType<Location>("Location");
    qDBusRegisterMetaType<Location>();
    qRegisterMetaType<QList<Location>>("QList<Location>");
    qDBusRegisterMetaType<QList<Location>>();
    qInfo() << "Meta types for Location registered.";
}

void CurrentWeather::registerMetaTypes()
{
    qRegisterMetaType<CurrentWeather>("CurrentWeather");
    qDBusRegisterMetaType<CurrentWeather>();
    qInfo() << "Meta types for CurrentWeather registered.";
}

void FutureWeather::registerMetaTypes()
{
    qRegisterMetaType<FutureWeather>("FutureWeather");
    qDBusRegisterMetaType<FutureWeather>();
    qRegisterMetaType<QList<FutureWeather>>("QList<FutureWeather>");
    qDBusRegisterMetaType<QList<FutureWeather>>();
    qInfo() << "Meta types for FutureWeather registered.";
}

QDBusArgument &operator<<(QDBusArgument &argument, const Location &data)
{
    argument.beginStructure();
    argument << data.name;
    argument << data.id;
    argument << data.latitude;
    argument << data.longitude;
    argument << data.adm2;
    argument << data.adm1;
    argument << data.country;
    argument << data.timezone;
    argument << data.utcOffset;
    argument << data.isDst;
    argument << data.type;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Location &data)
{
    argument.beginStructure();
    argument >> data.name;
    argument >> data.id;
    argument >> data.latitude;
    argument >> data.longitude;
    argument >> data.adm2;
    argument >> data.adm1;
    argument >> data.country;
    argument >> data.timezone;
    argument >> data.utcOffset;
    argument >> data.isDst;
    argument >> data.type;
    argument.endStructure();
    return argument;
}

QDebug operator<<(QDebug debug, const Location &data)
{
    debug << "{";
    debug << data.name << ",";
    debug << data.id << ",";
    debug << data.latitude << ",";
    debug << data.longitude << ",";
    debug << data.adm2 << ",";
    debug << data.adm1 << ",";
    debug << data.country << ",";
    debug << data.timezone << ",";
    debug << data.utcOffset << ",";
    debug << data.isDst << ",";
    debug << data.type << "}";
    return debug;
}

void CurrentWeather::changeTemperatureUnit(TemperatureUnit unit)
{
    double temper, feelsLike;
    if (unit == TemperatureUnit::FAHRENHEIT) {
        temper = celsiusToFahrenheit(this->temperature);
        feelsLike = celsiusToFahrenheit(this->feelsLikeTemperature);
    } else {
        temper = fahrenheitToCelsius(this->temperature);
        feelsLike = fahrenheitToCelsius(this->feelsLikeTemperature);
    }
    this->temperature = temper;
    this->feelsLikeTemperature = feelsLike;
    this->temperatureUnit = unit;
}

QDBusArgument &operator<<(QDBusArgument &argument, const CurrentWeather &data)
{
    argument.beginStructure();
    argument << data.observedTime.toTime_t();
    argument << data.temperatureUnit;
    argument << data.temperature;
    argument << data.feelsLikeTemperature;
    argument << data.iconName;
    argument << data.description;
    argument << data.wind360;
    argument << data.windDirection;
    argument << data.windSpeed;
    argument << data.humidity;
    argument << data.precip;
    argument << data.pressure;
    argument << data.visibility;
    argument << data.cloud;
    argument << data.dew;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, CurrentWeather &data)
{
    argument.beginStructure();
    uint timeStamp;
    argument >> timeStamp;
    data.observedTime.setTime_t(timeStamp);
    argument >> data.temperatureUnit;
    argument >> data.temperature;
    argument >> data.feelsLikeTemperature;
    argument >> data.iconName;
    argument >> data.description;
    argument >> data.wind360;
    argument >> data.windDirection;
    argument >> data.windSpeed;
    argument >> data.humidity;
    argument >> data.precip;
    argument >> data.pressure;
    argument >> data.visibility;
    argument >> data.cloud;
    argument >> data.dew;
    argument.endStructure();
    return argument;
}

QDebug operator<<(QDebug debug, const CurrentWeather &data)
{
    debug << "{";
    debug << data.observedTime.toTime_t() << ",";
    debug << data.temperatureUnit << ",";
    debug << data.temperature << ",";
    debug << data.feelsLikeTemperature << ",";
    debug << data.iconName << ",";
    debug << data.description << ",";
    debug << data.wind360 << ",";
    debug << data.windDirection << ",";
    debug << data.windSpeed << ",";
    debug << data.humidity << ",";
    debug << data.precip << ",";
    debug << data.pressure << ",";
    debug << data.visibility << ",";
    debug << data.cloud << ",";
    debug << data.dew << "}";
    return debug;
}

QDebug operator<<(QDebug debug, const FutureWeather &weather)
{
    debug << "{forecastDate: " << weather.forecastDate << " sunriseTime: " << weather.sunriseTime
          << " sunsetTime: " << weather.sunsetTime << " moonriseTime: " << weather.moonriseTime
          << " moonsetTime: " << weather.moonsetTime << " moonPhase: " << weather.moonPhase
          << " moonPhaseIcon: " << weather.moonPhaseIcon << " temperatureUnit: " << weather.temperatureUnit
          << " maxTemperature: " << weather.maxTemperature << " minTemperature: " << weather.minTemperature
          << " iconDay: " << weather.iconDay << " textDay: " << weather.textDay << " iconNight: " << weather.iconNight
          << " textNight: " << weather.textNight << " wind360Day: " << weather.wind360Day
          << " windDirectionDay: " << weather.windDirectionDay << " windScaleDay: " << weather.windScaleDay
          << " windSpeedDay: " << weather.windSpeedDay << " wind360Night: " << weather.wind360Night
          << " windDirectionNight: " << weather.windDirectionNight << " windScaleNight: " << weather.windScaleNight
          << " windSpeedNight: " << weather.windSpeedNight << " humidity: " << weather.humidity << " precip: " << weather.precip
          << " pressure: " << weather.pressure << " visibility: " << weather.visibility << " cloud: " << weather.cloud
          << " uvIndex: " << weather.uvIndex << "}";
    return debug;
}

QDBusArgument &operator<<(QDBusArgument &arg, const FutureWeather &weather)
{
    arg.beginStructure();
    arg << weather.forecastDate;
    arg << weather.sunriseTime;
    arg << weather.sunsetTime;
    arg << weather.moonriseTime;
    arg << weather.moonsetTime;
    arg << weather.moonPhase;
    arg << weather.moonPhaseIcon;
    arg << weather.temperatureUnit;
    arg << weather.maxTemperature;
    arg << weather.minTemperature;
    arg << weather.iconDay;
    arg << weather.textDay;
    arg << weather.iconNight;
    arg << weather.textNight;
    arg << weather.wind360Day;
    arg << weather.windDirectionDay;
    arg << weather.windScaleDay;
    arg << weather.windSpeedDay;
    arg << weather.wind360Night;
    arg << weather.windDirectionNight;
    arg << weather.windScaleNight;
    arg << weather.windSpeedNight;
    arg << weather.humidity;
    arg << weather.precip;
    arg << weather.pressure;
    arg << weather.visibility;
    arg << weather.cloud;
    arg << weather.uvIndex;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>>(const QDBusArgument &arg, FutureWeather &weather)
{
    arg.beginStructure();
    arg >> weather.forecastDate;
    arg >> weather.sunriseTime;
    arg >> weather.sunsetTime;
    arg >> weather.moonriseTime;
    arg >> weather.moonsetTime;
    arg >> weather.moonPhase;
    arg >> weather.moonPhaseIcon;
    arg >> weather.temperatureUnit;
    arg >> weather.maxTemperature;
    arg >> weather.minTemperature;
    arg >> weather.iconDay;
    arg >> weather.textDay;
    arg >> weather.iconNight;
    arg >> weather.textNight;
    arg >> weather.wind360Day;
    arg >> weather.windDirectionDay;
    arg >> weather.windScaleDay;
    arg >> weather.windSpeedDay;
    arg >> weather.wind360Night;
    arg >> weather.windDirectionNight;
    arg >> weather.windScaleNight;
    arg >> weather.windSpeedNight;
    arg >> weather.humidity;
    arg >> weather.precip;
    arg >> weather.pressure;
    arg >> weather.visibility;
    arg >> weather.cloud;
    arg >> weather.uvIndex;
    arg.endStructure();
    return arg;
}

END_USER_NAMESPACE
