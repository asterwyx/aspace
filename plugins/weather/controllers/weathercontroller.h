#pragma once
#include "common_def.h"
#include "models/currentweathermodel.h"
#include "models/futureweathermodel.h"
#include "models/locationmodel.h"
#include "weatherinterface.h"
#include <QScopedPointer>
#include <QSharedPointer>



class WeatherController : public QObject
{
    Q_OBJECT
public:
    explicit WeatherController(QObject *parent = nullptr);
    ~WeatherController() override;
    QDateTime getUpdateTime();

public slots:
    void updateCurrentWeather();
    void updateFutureWeather();
    QList<Location> lookForLocations(const QString &cityName);
    void setLocation(const Location &location);

    void setCurrentWeatherModel(CurrentWeatherModel *model);
    QSharedPointer<CurrentWeatherModel> getCurrentWeatherModel();

    void setFutureWeatherModel(FutureWeatherModel *model);
    QSharedPointer<FutureWeatherModel> getFutureWeatherModel();

    void setLocationModel(LocationModel *model);
    QSharedPointer<LocationModel> getLocationModel();

private:
    QSharedPointer<CurrentWeatherModel> m_currentWeatherModel;
    QSharedPointer<FutureWeatherModel> m_futureWeatherModel;
    QSharedPointer<LocationModel> m_locationModel;
    QDBusConnection m_busConn;
    QScopedPointer<WeatherInterface> m_weatherDBusInterface;
    QDateTime m_updateTime;
};
