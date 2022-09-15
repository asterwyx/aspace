#pragma once
#include "common_def.h"
#include <QDBusAbstractAdaptor>
#include <QTimer>

#include "weatherdata.h"
#include "aspace.h"

BEGIN_USER_NAMESPACE
class WeatherService : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DBUS_WEATHER_INTERFACE_NAME)
public:
    static constexpr int SERVICE_TIME = 30000; // in milliseconds, actually 30 seconds
    explicit WeatherService(Aspace *parent = nullptr);
    ~WeatherService() override;

    inline Aspace *context() const
    {
        return dynamic_cast<Aspace *>(parent());
    }
signals:
    void currentWeatherUpdated(const CurrentWeather &currentWeather);
    void futureWeatherUpdated(const QList<FutureWeather> &futureWeather);

public slots:
    USER_NAMESPACE::CurrentWeather          getCurrentWeather(const QString &cityCode);
    QList<USER_NAMESPACE::FutureWeather>    getFutureWeather(const QString &cityCode);
    QList<USER_NAMESPACE::Location>         lookForLocations(const QString &cityName);

private:
    QScopedPointer<QTimer> m_serviceTimer;
};

END_USER_NAMESPACE