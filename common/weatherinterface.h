#pragma once

#include <QDBusAbstractInterface>
#include <QDBusPendingReply>
#include "common_def.h"
#include "weatherdata.h"

BEGIN_USER_NAMESPACE

class WeatherInterface : public QDBusAbstractInterface {
    Q_OBJECT
public:
    static inline const char * staticInterfaceName()
    {
        return DBUS_WEATHER_INTERFACE_NAME;
    }
public:
    WeatherInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent=nullptr);
    ~WeatherInterface() override;

signals:
    void currentWeatherUpdated(const CurrentWeather &currentWeather);
    void futureWeatherUpdated(const QList<FutureWeather> &futureWeather);

public slots:
    inline QDBusPendingReply<CurrentWeather> getCurrentWeather(const QString &cityCode)
    {
        QList<QVariant> argumentList;
        argumentList << cityCode;
        return asyncCallWithArgumentList(QLatin1String("getCurrentWeather"), argumentList);
    }

    inline QDBusPendingReply<QList<FutureWeather>> getFutureWeather(const QString &cityCode)
    {
        QList<QVariant> argumentList;
        argumentList << cityCode;
        return asyncCallWithArgumentList(QLatin1String("getFutureWeather"), argumentList);
    }

    inline QDBusPendingReply<QList<Location>> lookForLocations(const QString &cityName)
    {
        QList<QVariant> argumentList;
        argumentList << cityName;
        return asyncCallWithArgumentList(QLatin1String("lookForLocations"), argumentList);
    }

};

END_USER_NAMESPACE
