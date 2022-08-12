// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "weather.h"
#include <QDBusConnection>
#include <QDBusMetaType>
#include <QDebug>

#include "enumdbus.h"
BEGIN_USER_NAMESPACE
Weather::Weather(QObject *parent)
    : QObject(parent)
{
    QDBusConnection conn = QDBusConnection::sessionBus();
    conn.registerObject(DBUS_WEATHER_PATH, this, QDBusConnection::ExportNonScriptableContents | QDBusConnection::ExportAllContents);
    qDebug() << "weather object registered.";
    conn.registerService(DBUS_SERVICE_NAME);
    qDebug() << "org.deepin.aspace service registered.";
}

Weather::~Weather() = default;

void Weather::setLocation(QString location)
{
    m_currentWeather.location = location;
}

double Weather::getCurrentTemperature()
{
    return m_currentWeather.currentTemperature;
}

double Weather::getLowestTemperature()
{
    return m_currentWeather.lowestTemperature;
}

double Weather::getHighestTemperature()
{
    return m_currentWeather.highestTemperature;
}

TemperatureUnit Weather::getCurrentTemperatureUnit()
{
    return m_currentWeather.unit;
}

WeatherOverview Weather::getCurrentWeatherOverview()
{
    return m_currentWeather.overview;
}

WeatherData Weather::getCurrentWeather()
{
    // TODO implement the data acquiring.
    return m_currentWeather;
}

QList<WeatherData> Weather::getFutureWeather()
{
    // TODO implement the data acquiring.
    return {
        {WeatherOverview::SUNNY, TemperatureUnit::CELSIUS, 36, 30, 38, QString::fromUtf8("武汉")},
        {WeatherOverview::SUNNY, TemperatureUnit::CELSIUS, 34, 28, 38, QString::fromUtf8("北京")}
        };
}

void Weather::setTemperatureUnit(TemperatureUnit unit)
{
    m_currentWeather.changeTemperatureUnit(unit);
}

QString Weather::getLocation()
{
    return m_currentWeather.location;
}

void Weather::registerWeatherMetaTypes()
{
    qRegisterMetaType<WeatherData>("WeatherData");
    qDBusRegisterMetaType<WeatherData>();
    qRegisterMetaType<WeatherOverview>("WeatherOverview");
    qDBusRegisterMetaType<WeatherOverview>();
    qRegisterMetaType<TemperatureUnit>("TemperatureUnit");
    qDBusRegisterMetaType<TemperatureUnit>();
    qRegisterMetaType<QList<WeatherData>>("QList<WeatherData>");
    qDBusRegisterMetaType<QList<WeatherData>>();
    qDebug() << "meta types for weather registered.";
}

END_USER_NAMESPACE


