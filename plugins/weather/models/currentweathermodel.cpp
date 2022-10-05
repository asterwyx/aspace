#include "currentweathermodel.h"
#include <QDBusInterface>

BEGIN_USER_NAMESPACE
CurrentWeatherModel::CurrentWeatherModel(QObject *parent)
    : QObject(parent)
{
}

void CurrentWeatherModel::setCurrentWeather(const CurrentWeather &weather)
{
    m_currentWeather = weather;
    // Here we cannot easily decide whether a current weather is changed.
    // We regard the set of the current weather indicate a change.
    emit this->currentWeatherChanged(m_currentWeather);
}

CurrentWeather CurrentWeatherModel::getCurrentWeather()
{
    return m_currentWeather;
}

CurrentWeatherModel::~CurrentWeatherModel() = default;

END_USER_NAMESPACE