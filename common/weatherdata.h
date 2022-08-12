// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>
#include <QList>
#include <QDBusArgument>
#include <QDebug>

#include "global.h"

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

struct WeatherData {
    WeatherOverview overview;
    TemperatureUnit unit;
    double          currentTemperature;
    double          lowestTemperature;
    double          highestTemperature;
    QString         location;
    
    WeatherData(
        WeatherOverview overview = WeatherOverview::RAINY,
        TemperatureUnit unit = TemperatureUnit::CELSIUS,
        double currentTemperature = 0,
        double lowestTemperature = 0,
        double highestTemperature = 0,
        QString location = ""
        );
    
    void changeTemperatureUnit(TemperatureUnit unit);

    friend QDBusArgument        &operator<<(QDBusArgument &argument, const WeatherData &data);
    friend const QDBusArgument  &operator>>(const QDBusArgument &argument, WeatherData &data);
    friend QDebug               &operator<<(QDebug &debug, const WeatherData &data);
    
};

END_USER_NAMESPACE

Q_DECLARE_METATYPE(USER_NAMESPACE::WeatherData)
Q_DECLARE_METATYPE(QList<USER_NAMESPACE::WeatherData>)
Q_DECLARE_METATYPE(USER_NAMESPACE::WeatherOverview)
Q_DECLARE_METATYPE(USER_NAMESPACE::TemperatureUnit)
