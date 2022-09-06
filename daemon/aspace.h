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
#include <QNetworkAccessManager>

#include "common_def.h"
#include "weatherdata.h"

BEGIN_USER_NAMESPACE

class Aspace : public QObject, public QDBusContext
{
    Q_OBJECT
public:
    static constexpr uint REQUEST_TIMEOUT = 5000; // ms
    inline static const char * apiKey()
    {
        return "b3aeb3cb72a74857b66a1f423c15bb89";
    }

public:

    explicit Aspace(QObject *parent = nullptr);
    ~Aspace();
    
signals:
    void weatherUpdated(CurrentWeather current);
    void locationIdUpdated(QString cityCode);


public slots:
    bool                updateWeather(QString cityCode = "");
    bool                parseApiCode(int apiCode);
    bool                updateLocationId(const QString &name);
    void                setLocationName(QString location);
    void                setTemperatureUnit(TemperatureUnit unit);
    CurrentWeather      getCurrentWeather();
    // QList<WeatherData>  getFutureWeather();

private:
    CurrentWeather          m_currentWeather;
    QNetworkAccessManager   m_networkManager;
};

END_USER_NAMESPACE



