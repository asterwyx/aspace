#pragma once
#include "common_def.h"
#include "models/currentweathermodel.h"
#include "models/futureweathermodel.h"
#include "models/locationmodel.h"
#include "weatherinterface.h"
#include <QScopedPointer>
#include <QSharedPointer>

BEGIN_USER_NAMESPACE

class WeatherController : public QObject {
    Q_OBJECT
public:
    explicit WeatherController(QObject *parent = nullptr);
    ~WeatherController() override;
    QDateTime getUpdateTime();

public slots:
    void                            updateCurrentWeather();
    void                            updateFutureWeather();
    QList<USER_NAMESPACE::Location> lookForLocations(const QString &cityName);
    void                            setLocation(const USER_NAMESPACE::Location &location);

    void setWeatherModel(USER_NAMESPACE::CurrentWeatherModel *model);
    QSharedPointer<USER_NAMESPACE::CurrentWeatherModel> getCurrentWeatherModel();

    void setFutureWeatherModel(USER_NAMESPACE::FutureWeatherModel *model);
    QSharedPointer<USER_NAMESPACE::FutureWeatherModel> getFutureWeatherModel();

    void setLocationModel(USER_NAMESPACE::LocationModel *model);
    QSharedPointer<USER_NAMESPACE::LocationModel>   getLocationModel();

private:
    QSharedPointer<CurrentWeatherModel> m_currentWeatherModel;
    QSharedPointer<FutureWeatherModel>  m_futureWeatherModel;
    QSharedPointer<LocationModel>       m_locationModel;
    QDBusConnection                     m_busConn;
    QScopedPointer<WeatherInterface>    m_weatherDBusInterface;
    QDateTime                           m_updateTime;
};

END_USER_NAMESPACE
