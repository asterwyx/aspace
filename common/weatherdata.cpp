// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "weatherdata.h"
#include "enumdbus.h"

BEGIN_USER_NAMESPACE
WeatherData::WeatherData(
    WeatherOverview overview,
    TemperatureUnit unit,
    double currentTemperature,
    double lowestTemperature,
    double highestTemperature,
    QString location
    ) : m_weatherOverview(overview),
        m_unit(unit),
        m_currentTemperature(currentTemperature),
        m_lowestTemperature(lowestTemperature),
        m_highestTemperature(highestTemperature),
        m_location(location)
{}

WeatherData::~WeatherData() = default;

WeatherOverview WeatherData::getWeatherOverview() const
{
    return m_weatherOverview;
}

double WeatherData::getCurrentTemperature() const
{
    return m_currentTemperature;
}

double WeatherData::getLowestTemperature() const
{
    return m_lowestTemperature;
}

double WeatherData::getHighestTemperature() const
{
    return m_highestTemperature;
}

TemperatureUnit WeatherData::getTemperatureUnit() const
{
    return m_unit;
}

QString WeatherData::getLocation() const
{
    return m_location;
}

void WeatherData::setLocation(QString location)
{
    m_location = location;
}

void WeatherData::setWeatherOverview(WeatherOverview overview)
{
    m_weatherOverview = overview;
}

void WeatherData::setCurrentTemperature(double currentTemper)
{
    m_currentTemperature = currentTemper;
}

void WeatherData::setLowestTemperature(double lowestTemper)
{
    m_lowestTemperature = lowestTemper;
}

void WeatherData::setHighestTemperature(double highestTemper)
{
    m_highestTemperature = highestTemper;
}

void WeatherData::setTemperatureUnit(TemperatureUnit unit)
{
    m_unit = unit;
    if (unit == TemperatureUnit::FAHRENHEIT)
    {
        // celsius to fahrenheit
        double cLowest = m_lowestTemperature;
        double cHighest = m_highestTemperature;
        m_lowestTemperature = 9.0 / 5.0 * cLowest + 32.0;
        m_highestTemperature = 9.0 / 5.0 * cHighest + 32.0;
    }
    else
    {
        // fahrenheit to celsius
        double fLowest = m_lowestTemperature;
        double fHighest = m_highestTemperature;
        m_lowestTemperature = (5.0 / 9.0) * (fLowest - 32.0);
        m_highestTemperature = (5.0 / 9.0) * (fHighest - 32.0);
    }
}


QDBusArgument &operator<<(QDBusArgument &argument, const WeatherData &data)
{
    argument.beginStructure();
    argument << data.m_weatherOverview;
    argument << data.m_unit;
    argument << data.m_currentTemperature;
    argument << data.m_lowestTemperature;
    argument << data.m_highestTemperature;
    argument << data.m_location;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, WeatherData &data)
{
    argument.beginStructure();
    argument >> data.m_weatherOverview;
    argument >> data.m_unit;
    argument >> data.m_currentTemperature;
    argument >> data.m_lowestTemperature;
    argument >> data.m_highestTemperature;
    argument >> data.m_location;
    argument.endStructure();
    return argument;
}

QDebug &operator<<(QDebug &debug, const WeatherData &data)
{
    debug << "{";
    debug << data.m_weatherOverview << ",";
    debug << data.m_unit << ",";
    debug << data.m_currentTemperature << ",";
    debug << data.m_lowestTemperature << ",";
    debug << data.m_highestTemperature << ",";
    debug << data.m_location << "}";
    return debug;
}

END_USER_NAMESPACE
