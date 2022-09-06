#include "weathermodel.h"

#include <QDBusInterface>


BEGIN_USER_NAMESPACE
WeatherModel::WeatherModel(QObject *parent)
    : QObject(parent),
    m_currentWeather(),
    m_busConn(QDBusConnection::sessionBus())
{
    m_weatherDBusInterface = new WeatherInterface(DBUS_SERVICE_NAME, DBUS_ASPACE_PATH, m_busConn);
}

void WeatherModel::updateCurrentWeather()
{
    QDBusPendingReply<CurrentWeather> weather = m_weatherDBusInterface->getCurrentWeather();
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(weather, this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *self) {
        QDBusPendingReply<CurrentWeather> reply(*self);
        if (reply.isError())
        {
            qWarning() << reply.error().message();
        }
        else
        {
            m_currentWeather = reply.value();
            emit this->currentWeatherUpdated(m_currentWeather);
        }
        self->deleteLater();
    });
}

CurrentWeather WeatherModel::getCurrentWeather()
{
    return m_currentWeather;
}


END_USER_NAMESPACE