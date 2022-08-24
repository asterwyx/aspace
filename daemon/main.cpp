// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QCoreApplication>
#include <QDebug>
#include "weatherservice.h"


USE_USER_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    utils::registerAllMetaTypes();
    Aspace asp;
    asp.setLocationName(QString::fromUtf8("武汉"));
    QDBusConnection connection = QDBusConnection::sessionBus();
    WeatherService ws(&asp);
    if (connection.registerService(DBUS_SERVICE_NAME) && connection.registerObject(DBUS_ASPACE_PATH, &asp, QDBusConnection::ExportAdaptors))
    {
        qInfo() << "Successfully registered service" << DBUS_SERVICE_NAME << "and object" << DBUS_ASPACE_PATH".";
    }
    else
    {
        qCritical() << "Cannot get a DBus service name, is another process running?";
        app.quit();
    }
    return app.exec();
}
