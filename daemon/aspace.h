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

#include "global.h"
#include "weatherdata.h"

BEGIN_USER_NAMESPACE

class Aspace : public QObject, public QDBusContext
{
    Q_OBJECT
    inline static const char * apiKey()
    {
        return "b3aeb3cb72a74857b66a1f423c15bb89";
    }

public:

    explicit Aspace(QObject *parent = nullptr);
    ~Aspace();
    
signals:
    void weatherChanged(WeatherData current);
    void cityCodeUpdated(QString cityCode);


public slots:
    void                updateWeather(QString cityCode = "");
    bool                parseApiCode(int apiCode);
    bool                getCityCode(const QString &name);
    void                setLocation(QString location);
    void                setTemperatureUnit(TemperatureUnit unit);
    WeatherData         getCurrentWeather();
    QList<WeatherData>  getFutureWeather();

private:
    WeatherData             m_currentWeather;
    QString                 m_cityCode;
    QNetworkAccessManager   *m_networkManager;
};

END_USER_NAMESPACE



