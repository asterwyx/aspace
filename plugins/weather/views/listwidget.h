#pragma once
#include "common_def.h"
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include "weathericon.h"
#include "weatherdata.h"



class ListWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit ListWidget(const FutureWeather *weather, QWidget *parent = nullptr);

    ~ListWidget() override;

private:
    WeatherIcon *m_weatherIcon;
    QLabel *m_sunriseTime;
    QLabel *m_maxTemperature;
    QLabel *m_minTemperature;
    QLabel *m_sunsetTime;
};
