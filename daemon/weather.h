// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>
#include <QList>
#include <QDBusArgument>

#include "global.h"
#include "weatherdata.h"

BEGIN_USER_NAMESPACE

class Weather : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DBUS_WEATHER_INTERFACE_NAME)
public:
    static void registerWeatherMetaTypes();
    explicit Weather(QObject *parent = nullptr);
    ~Weather();
signals:
    void weatherChanged(const USER_NAMESPACE::WeatherData& current);
    void temperatureChanged(int currentTemperature);
public slots:
    void                                setLocation(QString location);
    void                                setTemperatureUnit(USER_NAMESPACE::TemperatureUnit unit);
    QString                             getLocation();
    double                              getCurrentTemperature();
    double                              getLowestTemperature();
    double                              getHighestTemperature();
    USER_NAMESPACE::TemperatureUnit     getCurrentTemperatureUnit();
    USER_NAMESPACE::WeatherOverview     getCurrentWeatherOverview();
    USER_NAMESPACE::WeatherData         getCurrentWeather();
    QList<USER_NAMESPACE::WeatherData>  getFutureWeather();

private:
    WeatherData         m_currentWeather;
};

END_USER_NAMESPACE



