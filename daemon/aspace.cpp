// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "aspace.h"
#include <QDBusConnection>
#include <QDBusMetaType>
#include <QDebug>
#include <QDBusError>
#include <QCoreApplication>

BEGIN_USER_NAMESPACE
Aspace::Aspace(QObject *parent) : QObject(parent) {}

Aspace::~Aspace() = default;

void Aspace::setLocation(QString location)
{
    m_currentWeather.location = location;
}

WeatherData Aspace::getCurrentWeather()
{
    // TODO implement the data acquiring.
    return m_currentWeather;
}

QList<WeatherData> Aspace::getFutureWeather()
{
    // TODO implement the data acquiring.
    return {
        {WeatherOverview::SUNNY, TemperatureUnit::CELSIUS, 36, 30, 38, QString::fromUtf8("武汉")},
        {WeatherOverview::SUNNY, TemperatureUnit::CELSIUS, 34, 28, 38, QString::fromUtf8("北京")}
        };
}

void Aspace::setTemperatureUnit(TemperatureUnit unit)
{
    m_currentWeather.changeTemperatureUnit(unit);
}
END_USER_NAMESPACE
