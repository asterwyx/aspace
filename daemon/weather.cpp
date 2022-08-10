// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "weather.h"
#include "weather_p.h"
#include <QDBusConnection>
#include <QDBusMetaType>
#include <QDebug>

#include "enumdbus.h"
BEGIN_USER_NAMESPACE
Weather::Weather(QObject *parent)
    : QObject{parent}, d_ptr{new WeatherPrivate(this)}
{
    QDBusConnection conn = QDBusConnection::sessionBus();
    conn.registerObject("/weather", this, QDBusConnection::ExportNonScriptableContents | QDBusConnection::ExportAllContents);
    qDebug() << "weather object registered.";
    conn.registerService("org.deepin.aspace");
    qDebug() << "org.deepin.aspace service registered.";
}

Weather::~Weather()
{
    delete this->d_ptr;
}

void Weather::setLocation(QString location)
{
    Q_D(Weather);
    d->m_currentWeather.setLocation(location);
}

double Weather::getCurrentTemperature()
{
    // TODO implement data acquiring.
    Q_D(Weather);
    return d->m_currentWeather.getCurrentTemperature();
}

TemperatureUnit Weather::getCurrentTemperatureUnit()
{
    Q_D(Weather);
    return d->m_currentWeather.getTemperatureUnit();
}

WeatherOverview Weather::getCurrentWeatherOverview()
{
    // TODO implement the data acquiring.
    Q_D(Weather);
    return d->m_currentWeather.getWeatherOverview();
}

WeatherData Weather::getCurrentWeather()
{
    Q_D(Weather);
    return d->m_currentWeather;
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
    Q_D(Weather);
    d->m_currentWeather.setTemperatureUnit(unit);
}

QString Weather::getLocation()
{
    Q_D(Weather);
    return d->m_currentWeather.getLocation();
}

WeatherPrivate::WeatherPrivate(Weather *q)
    : q_ptr{q}
{}

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


