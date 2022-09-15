// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QCoreApplication>
#include <QDebug>
#include "weatherservice.h"
#include <QScopedPointer>
#include <DConfig>
DCORE_USE_NAMESPACE


USE_USER_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    utils::registerAllMetaTypes();
    Aspace asp;
    QDBusConnection connection = QDBusConnection::sessionBus();
    WeatherService ws(&asp);
    if (connection.registerService(DBUS_SERVICE_NAME) && connection.registerObject(DBUS_ASPACE_PATH, &asp, QDBusConnection::ExportAdaptors))
    {
        qInfo() << "Successfully registered service" << DBUS_SERVICE_NAME << "and object" << DBUS_ASPACE_PATH".";
        QScopedPointer<DConfig> config(DConfig::create("org.deepin.aspace", DCONFIG_FILE));
        if (config->isValid())
        {
            QString cityCode = config->value("locationId").toString();
            if (!cityCode.isEmpty())
            {
                // update current weather and future weather, emit signals
                bool ok = false;
                CurrentWeather weather = asp.getCurrentWeather(cityCode, &ok);
                if (ok)
                {
                    emit ws.currentWeatherUpdated(weather);
                }
                QList<FutureWeather> futureWeather = asp.getFutureWeather(cityCode, &ok);
                if (ok)
                {
                    emit ws.futureWeatherUpdated(futureWeather);
                }
            }
        }
    }
    else
    {
        qCritical() << "Cannot get a DBus service name, is another process running?";
        app.quit();
    }
    return app.exec();
}
