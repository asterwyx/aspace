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
    QByteArray              m_svgData;
    bool                    m_loaded;    // If there is an actual svg icon loaded.
};
END_USER_NAMESPACE
