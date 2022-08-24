// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "weatherdata.h"
#include "enumdbus.h"
#include <QDBusMetaType>

BEGIN_USER_NAMESPACE

namespace utils {
void registerAllMetaTypes()
{
    qRegisterMetaType<TemperatureUnit>("TemperatureUnit");
    qDBusRegisterMetaType<TemperatureUnit>();
    qInfo() << "Meta types for TemperatureUnit registered.";
    Location::registerMetaTypes();
    CurrentWeather::registerMetaTypes();
}
}

void Location::registerMetaTypes()
{
    qRegisterMetaType<Location>("Location");
    qDBusRegisterMetaType<Location>();
    qRegisterMetaType<QList<Location>>("QList<Location>");
    qDBusRegisterMetaType<QList<Location>>();
    qInfo() << "Meta types for Location registered.";

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

QDebug &operator<<(QDebug &debug, const Location &data)
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


void CurrentWeather::registerMetaTypes()
{
    qRegisterMetaType<CurrentWeather>("CurrentWeather");
    qDBusRegisterMetaType<CurrentWeather>();
    qInfo() << "Meta types for CurrentWeather registered.";
}

void CurrentWeather::changeTemperatureUnit(TemperatureUnit unit)
{
    double temper, feelsLike;
    if (unit == TemperatureUnit::FAHRENHEIT)
    {
        temper = celsiusToFahrenheit(this->temperature);
        feelsLike = celsiusToFahrenheit(this->feelsLikeTemperature);
    }
    else
    {
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
    argument << data.location;
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
    argument >> data.location;
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


QDebug &operator<<(QDebug &debug, const CurrentWeather &data)
{
    debug << "{";
    debug << data.location << ",";
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


// WeatherData::WeatherData(
//     WeatherOverview overview,
//     TemperatureUnit unit,
//     double currentTemperature,
//     double lowestTemperature,
//     double highestTemperature,
//     QString location
//     ) : overview(overview),
//         unit(unit),
//         currentTemperature(currentTemperature),
//         lowestTemperature(lowestTemperature),
//         highestTemperature(highestTemperature),
//         location(location)
// {}

// void WeatherData::changeTemperatureUnit(TemperatureUnit unit)
// {
//     this->unit = unit;
//     if (unit == TemperatureUnit::FAHRENHEIT)
//     {
//         // celsius to fahrenheit
//         double cCurrent = currentTemperature;
//         double cLowest = lowestTemperature;
//         double cHighest = highestTemperature;
//         currentTemperature = 9.0 / 5.0 * cCurrent + 32.0;
//         lowestTemperature = 9.0 / 5.0 * cLowest + 32.0;
//         highestTemperature = 9.0 / 5.0 * cHighest + 32.0;
//     }
//     else
//     {
//         // fahrenheit to celsius
//         double fCurrent = currentTemperature;
//         double fLowest = lowestTemperature;
//         double fHighest = highestTemperature;
//         currentTemperature = (5.0 / 9.0) * (fCurrent - 32.0);
//         lowestTemperature = (5.0 / 9.0) * (fLowest - 32.0);
//         highestTemperature = (5.0 / 9.0) * (fHighest - 32.0);
//     }
// }

// void WeatherData::registerMetaTypes()
// {
//     qRegisterMetaType<WeatherData>("WeatherData");
//     qDBusRegisterMetaType<WeatherData>();
//     qRegisterMetaType<WeatherOverview>("WeatherOverview");
//     qDBusRegisterMetaType<WeatherOverview>();
//     qRegisterMetaType<TemperatureUnit>("TemperatureUnit");
//     qDBusRegisterMetaType<TemperatureUnit>();
//     qRegisterMetaType<QList<WeatherData>>("QList<WeatherData>");
//     qDBusRegisterMetaType<QList<WeatherData>>();
//     qDebug() << "Meta types for weather registered.";
// }


// QDBusArgument &operator<<(QDBusArgument &argument, const WeatherData &data)
// {
//     argument.beginStructure();
//     argument << data.overview;
//     argument << data.unit;
//     argument << data.currentTemperature;
//     argument << data.lowestTemperature;
//     argument << data.highestTemperature;
//     argument << data.location;
//     argument.endStructure();
//     return argument;
// }

// const QDBusArgument &operator>>(const QDBusArgument &argument, WeatherData &data)
// {
//     argument.beginStructure();
//     argument >> data.overview;
//     argument >> data.unit;
//     argument >> data.currentTemperature;
//     argument >> data.lowestTemperature;
//     argument >> data.highestTemperature;
//     argument >> data.location;
//     argument.endStructure();
//     return argument;
// }

// QDebug &operator<<(QDebug &debug, const WeatherData &data)
// {
//     debug << "{";
//     debug << data.overview << ",";
//     debug << data.unit << ",";
//     debug << data.currentTemperature << ",";
//     debug << data.lowestTemperature << ",";
//     debug << data.highestTemperature << ",";
//     debug << data.location << "}";
//     return debug;
// }

END_USER_NAMESPACE
