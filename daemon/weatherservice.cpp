#include "weatherservice.h"
#include <QCoreApplication>
#include <utility>

BEGIN_USER_NAMESPACE

WeatherService::WeatherService(Aspace *parent)
    : QDBusAbstractAdaptor(parent)
    , m_serviceTimer(new QTimer)
{
    setAutoRelaySignals(true);
    m_serviceTimer->setInterval(SERVICE_TIME);
#if not defined(PERSISTENT_DAEMON)
    connect(m_serviceTimer.data(), &QTimer::timeout, qApp, &QCoreApplication::quit);
#endif
    m_serviceTimer->start();
}

WeatherService::~WeatherService() = default;

CurrentWeather WeatherService::getCurrentWeather(const QString &cityCode)
{
    m_serviceTimer->start();
    return context()->getCurrentWeather(cityCode);
}

QList<FutureWeather> WeatherService::getFutureWeather(const QString &cityCode)
{
    m_serviceTimer->start();
    return context()->getFutureWeather(cityCode);
}

QList<Location> WeatherService::lookForLocations(const QString &cityName)
{
    m_serviceTimer->start();
    return context()->lookForLocations(cityName);
}

END_USER_NAMESPACE