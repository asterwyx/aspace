#pragma once

#include <QDBusAbstractInterface>
#include <QDBusPendingReply>
#include "common_def.h"
#include "weatherdata.h"

BEGIN_USER_NAMESPACE

class WeatherInterface : QDBusAbstractInterface {
    Q_OBJECT
public:
    static inline const char * staticInterfaceName()
    {
        return DBUS_WEATHER_INTERFACE_NAME;
    }
public:
    WeatherInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent=nullptr);
    ~WeatherInterface();

public slots:
    inline QDBusPendingReply<CurrentWeather> getCurrentWeather()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("getCurrentWeather"), argumentList);
    }

    // inline QDBusPendingReply<WeatherData> getFutureWeather()
    // {
    //     QList<QVariant> argumentList;
    //     return asyncCallWithArgumentList(QLatin1String("getFutureWeather"), argumentList);
    // }
signals:
    void weatherUpdated(CurrentWeather weather);
    void quitService();
};

END_USER_NAMESPACE
