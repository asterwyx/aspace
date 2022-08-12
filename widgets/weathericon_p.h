// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "weathericon.h"
#include <QPixmap>
#include <QString>

BEGIN_USER_NAMESPACE
class WeatherIconPrivate {
public:
    WeatherIconPrivate(WeatherIcon *q);
    ~WeatherIconPrivate();


private:
    Q_DECLARE_PUBLIC(WeatherIcon)
    double                  m_scaleFactor;
    WeatherIcon             *q_ptr;
    QString                 m_iconPath;
    QColor                  m_iconColor; // This is only valid for svg icon
    WeatherIcon::IconType   m_iconType;
    QByteArray              m_svgData;
    QPixmap                 m_iconPixmap;
};
END_USER_NAMESPACE
