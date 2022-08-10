// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>
#include <QList>
#include <QDBusArgument>

#include "namespace.h"
#include "weatherdata.h"

BEGIN_USER_NAMESPACE

class WeatherPrivate;

class Weather : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.deepin.aspace.Weather")
public:
    static Weather *getInstance()
    {
        static Weather instance;
        return &instance;
    }
    static void registerWeatherMetaTypes();
    Q_DISABLE_COPY(Weather)
protected:
    explicit Weather(QObject *parent = nullptr);
    ~Weather();
signals:
    void weatherChanged(USER_NAMESPACE::WeatherOverview current);
    void temperatureChanged(int currentTemperature);
public slots:
    void                                setLocation(QString location);
    void                                setTemperatureUnit(USER_NAMESPACE::TemperatureUnit unit);
    QString                             getLocation();
    double                              getCurrentTemperature();
    USER_NAMESPACE::TemperatureUnit     getCurrentTemperatureUnit();
    USER_NAMESPACE::WeatherOverview     getCurrentWeatherOverview();
    USER_NAMESPACE::WeatherData         getCurrentWeather();
    QList<USER_NAMESPACE::WeatherData>  getFutureWeather();

private:
    Q_DECLARE_PRIVATE(Weather)
    WeatherPrivate *d_ptr;
};

END_USER_NAMESPACE



