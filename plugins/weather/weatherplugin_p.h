// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "weatherplugin.h"
#include <QDBusConnection>
#include <QDBusInterface>
BEGIN_USER_NAMESPACE
class WeatherPluginPrivate {
public:
    WeatherPluginPrivate(WeatherPlugin *q);
    ~WeatherPluginPrivate();
private:
    Q_DECLARE_PUBLIC(WeatherPlugin)
    WeatherPlugin   *q_ptr;
    QWidget         *m_exportedWidget;
    QString         m_weatherIconName;
    QString         m_locationLabelName;
    QString         m_temperatureLabelName;
    QSize           m_size;
};
END_USER_NAMESPACE