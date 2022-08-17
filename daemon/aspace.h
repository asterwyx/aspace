// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <QObject>
#include <QList>
#include <QDBusArgument>
#include <QDBusConnection>
#include <QTimer>
#include <QDBusContext>

#include "global.h"
#include "weatherdata.h"

BEGIN_USER_NAMESPACE

class Aspace : public QObject, public QDBusContext
{
    Q_OBJECT
public:

    explicit Aspace(QObject *parent = nullptr);
    ~Aspace();
    
signals:
    void weatherChanged(const USER_NAMESPACE::WeatherData& current);
    void temperatureChanged(int currentTemperature);
public slots:
    void                                setLocation(QString location);
    void                                setTemperatureUnit(USER_NAMESPACE::TemperatureUnit unit);
    USER_NAMESPACE::WeatherData         getCurrentWeather();
    QList<USER_NAMESPACE::WeatherData>  getFutureWeather();

// private slots:
    // void registerDBus();
    // void unregisterDBus();

private:
    WeatherData             m_currentWeather;
    // QDBusConnection         m_conn;
};

END_USER_NAMESPACE



