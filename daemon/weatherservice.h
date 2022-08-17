#pragma once
#include "global.h"
#include <QDBusAbstractAdaptor>
#include <QTimer>

#include "weatherdata.h"
#include "aspace.h"

BEGIN_USER_NAMESPACE
class WeatherService : QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DBUS_WEATHER_INTERFACE_NAME)
public:
    static constexpr int SERVICE_TIME = 30000; // in milliseconds, actually 30 seconds
    explicit WeatherService(Aspace *parent = nullptr);
    virtual ~WeatherService();

    inline Aspace *parent() const;

public slots:
    WeatherData getCurrentWeather();
    QList<WeatherData> getFutureWeather();

signals:
    void weatherUpdated(WeatherData weather);
    void quitService();
private:
    QScopedPointer<QTimer> m_serviceTimer;
};

END_USER_NAMESPACE