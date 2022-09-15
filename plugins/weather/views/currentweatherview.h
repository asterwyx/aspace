//
// Created by astrea on 9/13/22.
//
#pragma once
#include "common_def.h"
#include <QVBoxLayout>
#include <QWidget>
#include "weathericon.h"
#include <QLabel>

BEGIN_USER_NAMESPACE
class CurrentWeatherView : public QWidget {


private:
    QVBoxLayout     *m_layout;
    WeatherIcon     *m_weatherIcon;
};

END_USER_NAMESPACE
