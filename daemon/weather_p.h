// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "weather.h"

BEGIN_USER_NAMESPACE
class WeatherPrivate {
public:
    explicit WeatherPrivate(Weather *q);

private:
    Q_DECLARE_PUBLIC(Weather)
    Weather                     *q_ptr;
    WeatherData                 m_currentWeather;
};

END_USER_NAMESPACE
