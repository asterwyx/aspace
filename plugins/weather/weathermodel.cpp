#include "weathermodel.h"

#include <QDBusInterface>


BEGIN_USER_NAMESPACE
WeatherModel::WeatherModel(QObject *parent)
    : QObject(parent)
{}


void WeatherModel::setCurrentWeather(const CurrentWeather &weather)
{
    m_currentWeather = weather;
    // Here we cannot easily decide whether a current weather is changed.
    // We regard the set of the current weather indicate a change.
    emit this->currentWeatherChanged(m_currentWeather);
}


CurrentWeather WeatherModel::getCurrentWeather()
{
    return m_currentWeather;
}


END_USER_NAMESPACE