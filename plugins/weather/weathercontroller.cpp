#include "weathercontroller.h"

BEGIN_USER_NAMESPACE
WeatherController::WeatherController(QObject *parent)
    : QObject(parent),
    m_model(new WeatherModel),
    m_busConn(QDBusConnection::sessionBus()),
    m_weatherDBusInterface(new WeatherInterface(DBUS_SERVICE_NAME, DBUS_ASPACE_PATH, m_busConn))
{}

void WeatherController::setWeatherModel(WeatherModel *model)
{
    m_model.reset(model);
}

QSharedPointer<WeatherModel> WeatherController::getWeatherModel()
{
    return m_model;
}

void WeatherController::updateCurrentWeather()
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
            m_model->setCurrentWeather(reply.value());
        }
        self->deleteLater();
    });
}

WeatherController::~WeatherController() {}


END_USER_NAMESPACE