// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "weather.h"
#include <QApplication>
#include <QDebug>

USE_USER_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto weather = new Weather();
    weather->setLocation(QString::fromUtf8("武汉"));
    weather->setTemperatureUnit(TemperatureUnit::FAHRENHEIT);
    Weather::registerWeatherMetaTypes();
    qDebug() << "daemon started.";
    return a.exec();
}
