#pragma once
#include "common_def.h"
#include "weathermodel.h"
#include "weatherinterface.h"
#include <QScopedPointer>
#include <QSharedPointer>

BEGIN_USER_NAMESPACE

class WeatherController : public QObject {
public:
    WeatherController(QObject *parent = nullptr);
    ~WeatherController();

public slots:
    void updateCurrentWeather();

    void setWeatherModel(WeatherModel *model);
    QSharedPointer<WeatherModel> getWeatherModel();

private:
    QSharedPointer<WeatherModel>        m_model;
    QDBusConnection                     m_busConn;
    QScopedPointer<WeatherInterface>    m_weatherDBusInterface;
};

END_USER_NAMESPACE
