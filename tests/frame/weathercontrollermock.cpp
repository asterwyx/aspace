#include "weathercontrollermock.h"
#include "controllers/weathercontroller.h"
#include <QDebug>
#include "weatherdata.h"

USE_USER_NAMESPACE

void updateCurrentWeatherStub(void *weatherController)
{
    auto *controller = static_cast<WeatherController *>(weatherController);
    auto currentWeatherModel = controller->getCurrentWeatherModel();
    CurrentWeather currentWeather = {.temperature = 1000, .iconName="1024", .description = "阿巴阿巴"};
    qDebug() << currentWeather;
    currentWeatherModel->setCurrentWeather(currentWeather);
}

void updateFutureWeatherStub(void *weatherController)
{
    auto *controller = static_cast<WeatherController *>(weatherController);
    auto futureWeatherModel = controller->getFutureWeatherModel();
    FutureWeather weather1{.maxTemperature = 1024, .minTemperature = -1024, .iconDay = "1024"};
    qDebug() << weather1;
    FutureWeather weather2{.maxTemperature = 512, .minTemperature = -512, .iconDay = "512"};
    QList<FutureWeather> futureWeather{weather1, weather2};
    futureWeatherModel->onFutureWeatherUpdated(futureWeather);
}

