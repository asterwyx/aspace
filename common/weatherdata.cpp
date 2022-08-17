// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "weatherdata.h"
#include "enumdbus.h"
#include <QDBusMetaType>

BEGIN_USER_NAMESPACE
WeatherData::WeatherData(
    WeatherOverview overview,
    TemperatureUnit unit,
    double currentTemperature,
    double lowestTemperature,
    double highestTemperature,
    QString location
    ) : overview(overview),
        unit(unit),
        currentTemperature(currentTemperature),
        lowestTemperature(lowestTemperature),
        highestTemperature(highestTemperature),
        location(location)
{}

void WeatherData::changeTemperatureUnit(TemperatureUnit unit)
{
    this->unit = unit;
    if (unit == TemperatureUnit::FAHRENHEIT)
    {
        // celsius to fahrenheit
        double cCurrent = currentTemperature;
        double cLowest = lowestTemperature;
        double cHighest = highestTemperature;
        currentTemperature = 9.0 / 5.0 * cCurrent + 32.0;
        lowestTemperature = 9.0 / 5.0 * cLowest + 32.0;
        highestTemperature = 9.0 / 5.0 * cHighest + 32.0;
    }
    else
    {
        // fahrenheit to celsius
        double fCurrent = currentTemperature;
        double fLowest = lowestTemperature;
        double fHighest = highestTemperature;
        currentTemperature = (5.0 / 9.0) * (fCurrent - 32.0);
        lowestTemperature = (5.0 / 9.0) * (fLowest - 32.0);
        highestTemperature = (5.0 / 9.0) * (fHighest - 32.0);
    }
}

void WeatherData::registerMetaTypes()
{
    qRegisterMetaType<WeatherData>("WeatherData");
    qDBusRegisterMetaType<WeatherData>();
    qRegisterMetaType<WeatherOverview>("WeatherOverview");
    qDBusRegisterMetaType<WeatherOverview>();
    qRegisterMetaType<TemperatureUnit>("TemperatureUnit");
    qDBusRegisterMetaType<TemperatureUnit>();
    qRegisterMetaType<QList<WeatherData>>("QList<WeatherData>");
    qDBusRegisterMetaType<QList<WeatherData>>();
    qDebug() << "Meta types for weather registered.";
}


QDBusArgument &operator<<(QDBusArgument &argument, const WeatherData &data)
{
    argument.beginStructure();
    argument << data.overview;
    argument << data.unit;
    argument << data.currentTemperature;
    argument << data.lowestTemperature;
    argument << data.highestTemperature;
    argument << data.location;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, WeatherData &data)
{
    argument.beginStructure();
    argument >> data.overview;
    argument >> data.unit;
    argument >> data.currentTemperature;
    argument >> data.lowestTemperature;
    argument >> data.highestTemperature;
    argument >> data.location;
    argument.endStructure();
    return argument;
}

QDebug &operator<<(QDebug &debug, const WeatherData &data)
{
    debug << "{";
    debug << data.overview << ",";
    debug << data.unit << ",";
    debug << data.currentTemperature << ",";
    debug << data.lowestTemperature << ",";
    debug << data.highestTemperature << ",";
    debug << data.location << "}";
    return debug;
}

END_USER_NAMESPACE
