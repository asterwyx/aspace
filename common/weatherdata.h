// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>
#include <QList>
#include <QDBusArgument>
#include <QDebug>

#include "namespace.h"

BEGIN_USER_NAMESPACE

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

class WeatherData {
public:
    WeatherData(
        WeatherOverview overview = WeatherOverview::SUNNY,
        TemperatureUnit unit = TemperatureUnit::CELSIUS,
        double currentTemperature = 0,
        double lowestTemperature = 0,
        double highestTemperature = 0,
        QString location = ""
        );
    ~WeatherData();
    WeatherOverview             getWeatherOverview() const;
    double                      getCurrentTemperature() const;
    double                      getLowestTemperature() const;
    double                      getHighestTemperature() const;
    TemperatureUnit             getTemperatureUnit() const;
    QString                     getLocation() const;

    void                        setWeatherOverview(WeatherOverview overview);
    void                        setCurrentTemperature(double currentTemper);
    void                        setLowestTemperature(double lowestTemper);
    void                        setHighestTemperature(double highestTemper);
    void                        setLocation(QString location);
    void                        setTemperatureUnit(TemperatureUnit unit);
    friend QDBusArgument        &operator<<(QDBusArgument &argument, const WeatherData &data);
    friend const QDBusArgument  &operator>>(const QDBusArgument &argument, WeatherData &data);
    friend QDebug               &operator<<(QDebug &debug, const WeatherData &data);

private:
    WeatherOverview m_weatherOverview;
    TemperatureUnit m_unit;
    double          m_currentTemperature;
    double          m_lowestTemperature;
    double          m_highestTemperature;
    QString         m_location;
};

END_USER_NAMESPACE

Q_DECLARE_METATYPE(USER_NAMESPACE::WeatherData)
Q_DECLARE_METATYPE(QList<USER_NAMESPACE::WeatherData>)
Q_DECLARE_METATYPE(USER_NAMESPACE::WeatherOverview)
Q_DECLARE_METATYPE(USER_NAMESPACE::TemperatureUnit)
