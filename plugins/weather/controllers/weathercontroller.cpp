#include "weathercontroller.h"

BEGIN_USER_NAMESPACE
WeatherController::WeatherController(QObject *parent)
    : QObject(parent),
      m_currentWeatherModel(new CurrentWeatherModel),
      m_futureWeatherModel(new FutureWeatherModel(nullptr)),
      m_locationModel(new LocationModel),
      m_busConn(QDBusConnection::sessionBus()),
      m_weatherDBusInterface(new WeatherInterface(DBUS_SERVICE_NAME, DBUS_ASPACE_PATH, m_busConn)),
      m_updateTime()
{
    connect(m_weatherDBusInterface.data(), &WeatherInterface::currentWeatherUpdated, [&](const CurrentWeather &weather){
        this->m_updateTime = QDateTime::currentDateTime();
        emit m_currentWeatherModel->currentWeatherChanged(weather);
    });
    connect(m_weatherDBusInterface.data(), &WeatherInterface::futureWeatherUpdated, [&](const QList<FutureWeather> &futureWeather)
    {
        this->m_updateTime = QDateTime::currentDateTime();
        m_futureWeatherModel->onFutureWeatherUpdated(futureWeather);
    });
}

void WeatherController::setWeatherModel(CurrentWeatherModel *model)
{
    m_currentWeatherModel.reset(model);
}

QSharedPointer<CurrentWeatherModel> WeatherController::getCurrentWeatherModel()
{
    return m_currentWeatherModel;
}

void WeatherController::updateCurrentWeather()
{
    QDBusPendingReply<CurrentWeather> weather = m_weatherDBusInterface->getCurrentWeather(m_locationModel->getLocationId());
    weather.waitForFinished();
    if (weather.isError())
    {
        qWarning() << weather.error().message();
    }
    else
    {
        m_updateTime = QDateTime::currentDateTime();
        m_currentWeatherModel->setCurrentWeather(weather.value());
    }
}

void WeatherController::updateFutureWeather()
{
    QDBusPendingReply<QList<FutureWeather>> futureWeather = m_weatherDBusInterface->getFutureWeather(m_locationModel->getLocationId());
    futureWeather.waitForFinished();
    if (futureWeather.isError())
    {
        qWarning() << futureWeather.error().message();
    }
    else
    {
        m_updateTime = QDateTime::currentDateTime();
        this->m_futureWeatherModel->onFutureWeatherUpdated(futureWeather.value());
    }
}

QList<Location> WeatherController::lookForLocations(const QString &cityName) {
    QDBusPendingReply<QList<Location>> locations = m_weatherDBusInterface->lookForLocations(cityName);
    QList<Location> result;
    auto *watcher = new QDBusPendingCallWatcher(locations, this);
    watcher->waitForFinished();
    if (locations.isError())
    {
        qWarning() << locations.error().message();
        result = {};
    }
    else
    {
        result = locations.value();
    }
    return result;
}

void WeatherController::setLocation(const Location &location) {
    this->m_locationModel->setLocation(location);
}

void WeatherController::setFutureWeatherModel(FutureWeatherModel *model) {
    this->m_futureWeatherModel.reset(model);
}

QSharedPointer<FutureWeatherModel> WeatherController::getFutureWeatherModel()
{
    return this->m_futureWeatherModel;
}

void WeatherController::setLocationModel(LocationModel *model)
{
    this->m_locationModel.reset(model);
}

QSharedPointer<LocationModel> WeatherController::getLocationModel()
{
    return this->m_locationModel;
}

QDateTime WeatherController::getUpdateTime()
{
    return m_updateTime;
}

WeatherController::~WeatherController() = default;

END_USER_NAMESPACE