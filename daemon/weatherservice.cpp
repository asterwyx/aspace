#include "weatherservice.h"
#include <QCoreApplication>

BEGIN_USER_NAMESPACE

WeatherService::WeatherService(Aspace *parent)
    : QDBusAbstractAdaptor(parent), m_serviceTimer(new QTimer)
{
    m_serviceTimer->setInterval(SERVICE_TIME);
    // Connect parent's signals
    connect(parent, &Aspace::weatherUpdated, this, [=](CurrentWeather weather) {emit this->weatherUpdated(weather);});
    connect(m_serviceTimer.data(), &QTimer::timeout, qApp, &QCoreApplication::quit);
    m_serviceTimer->start();
}

WeatherService::~WeatherService() {}

Aspace *WeatherService::parent() const
{
    return static_cast<Aspace *>(QObject::parent());
}

CurrentWeather WeatherService::getCurrentWeather()
{
    m_serviceTimer->start();
    return parent()->getCurrentWeather();
}

// QList<WeatherData> WeatherService::getFutureWeather()
// {
//     m_serviceTimer->start();
//     return parent()->getFutureWeather();
// }
END_USER_NAMESPACE