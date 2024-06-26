#include "weatherinterface.h"



WeatherInterface::WeatherInterface(const QString &service,
                                   const QString &path,
                                   const QDBusConnection &connection,
                                   QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

WeatherInterface::~WeatherInterface() = default;
