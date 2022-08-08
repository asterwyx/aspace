#include "weather.h"
#include "weather_p.h"

BEGIN_USER_NAMESPACE
Weather::Weather(QObject *parent)
    : QObject{parent}, d_ptr{new WeatherPrivate(this)}
{}

Weather::~Weather()
{
    delete this->d_ptr;
}

int Weather::getCurrentTemperature()
{
    // TODO implement data acquiring.
    return 0;
}

Weather::TemperatureUnit Weather::getCurrentTemperatureUnit()
{
    Q_D(Weather);
    return d->m_unit;
}

Weather::WeatherOverview Weather::getCurrentWeather()
{
    // TODO implement the data acquiring.
    return SUNNY;
}

QList<QPair<Weather::WeatherOverview, QPair<int, int> > > Weather::getNextFifteenDaysWeather()
{
    // TODO implement the data acquiring.
    return {};
}

void Weather::setTemperatureUnit(TemperatureUnit unit)
{
    Q_D(Weather);
    d->m_unit = unit;
}

WeatherPrivate::WeatherPrivate(Weather *q)
    : q_ptr{q}
{
    m_unit = Weather::CELSIUS;
}



END_USER_NAMESPACE
