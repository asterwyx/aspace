#include "weathercontrollermock.h"
#include "controllers/weathercontroller.h"
#include <QDebug>
#include "weatherdata.h"

USE_USER_NAMESPACE

void updateCurrentWeatherStub(void *weatherController)
{
    auto *controller = static_cast<WeatherController *>(weatherController);
    auto currentWeatherModel = controller->getCurrentWeatherModel();
    CurrentWeather currentWeather;
    currentWeatherModel->setCurrentWeather(currentWeather);
}

void updateFutureWeatherStub(void *weatherController)
{
    auto *controller = static_cast<WeatherController *>(weatherController);
    auto futureWeatherModel = controller->getFutureWeatherModel();
    FutureWeather weather1;
    FutureWeather weather2;
    QList<FutureWeather> futureWeather{weather1, weather2};
    futureWeatherModel->onFutureWeatherUpdated(futureWeather);
}

