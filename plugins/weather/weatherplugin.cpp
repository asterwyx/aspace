// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "weatherplugin.h"
#include "weatherplugin_p.h"
#include <QLabel>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QGroupBox>
#include <QFont>
#include <QDebug>
#include <QDBusArgument>

#include "weatherdata.h"
#include "weathericon.h"

#include "enumdbus.h"

BEGIN_USER_NAMESPACE

WeatherPlugin::WeatherPlugin() : d_ptr(new WeatherPluginPrivate(this)) {}
WeatherPlugin::~WeatherPlugin() = default;

QString WeatherPlugin::pluginName() const { return {"dde-weather"}; }
QString WeatherPlugin::pluginDisplayName() const { return {"Weather"}; }

QWidget *WeatherPlugin::pluginWidget(const QString &key) {
    Q_UNUSED(key)
    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusInterface *iface = new QDBusInterface("org.deepin.aspace",
                                                  "/weather",
                                             "org.deepin.aspace.Weather",
                                            bus,
                                                this);
    QDBusMessage overviewMsg = iface->call("getCurrentWeatherOverview");
    WeatherData data;
    if (overviewMsg.type() == QDBusMessage::ErrorMessage)
    {
        qWarning() << "call getCurrentWeatherOverview unsuccessfully.";
    }
    else if (overviewMsg.type() == QDBusMessage::ReplyMessage)
    {
        qDebug() << "call getCurrentWeatherOverviewSuccessfully.";
        // For complex types, we might encounter signature mismatch problem,
        // although we've overwrite the >> operator of enum WeatherOverview and 
        // enum TemperatureUnit. So we should unmarshal it manually.
        WeatherOverview overview = qdbus_cast<WeatherOverview>(overviewMsg.arguments().takeFirst());
        data.setWeatherOverview(overview);
    }
    else
    {
        qWarning() << "Unknown message type.";
    }
    // For simple and well-defind types by Qt like QString, we could use QDBusReply wrapper
    QDBusReply<double> temperReply = iface->call("getCurrentTemperature");
    if (temperReply.isValid())
    {
        qDebug() << "call getCurrentTemperature successfully.";
        data.setCurrentTemperature(temperReply.value());
    }
    QDBusReply<QString> locationReply = iface->call("getLocation");
    if (locationReply.isValid())
    {
        qDebug() << "call getLocation successfully.";
        data.setLocation(locationReply.value());
    }
    QDBusMessage unitMsg = iface->call("getCurrentTemperatureUnit");
    if (unitMsg.type() == QDBusMessage::ErrorMessage)
    {
        qWarning() << "call getCurrentTemperatureUnit unsuccessfully.";
    }
    else if (unitMsg.type() == QDBusMessage::ReplyMessage)
    {
        qDebug() << "call getCurrentTemperatureUnit successfully.";
        TemperatureUnit unit = qdbus_cast<TemperatureUnit>(unitMsg.arguments().takeFirst());
        data.setTemperatureUnit(unit);
    }
    QDBusMessage futureWeatherMsg = iface->call("getFutureWeather");
    auto arguments = futureWeatherMsg.arguments();
    qDebug() << arguments.size();
    QList<WeatherData> futureWeather = qdbus_cast<QList<WeatherData>>(arguments.takeFirst());
    qDebug() << futureWeather;
    auto box = new QGroupBox();
    auto temperLabel = new QLabel(box);
    QString temperString = QString::number(data.getCurrentTemperature(), 10, 0);
    temperString += "\u00B0"; // add degree character °
    if (data.getTemperatureUnit() == TemperatureUnit::CELSIUS)
    {
        temperString += "C";
    }
    else
    {
        temperString += "F";
    }
    temperLabel->setText(temperString);
    auto locationLabel = new QLabel(data.getLocation(), box);
    QFont locationFont("Noto Sans CJK SC");
    locationFont.setWeight(100);
    locationFont.setPointSize(16);
    temperLabel->setFont(locationFont);
    temperLabel->resize(2 * temperLabel->size());
    locationLabel->setFont(locationFont);
    WeatherIcon *icon;
    switch (data.getWeatherOverview())
    {
    case WeatherOverview::SUNNY:
        icon = new WeatherIcon(":/icons/sunny.svg", box, 9);
        break;
    case WeatherOverview::RAINY:
        icon = new WeatherIcon(":/icons/slightly_rainy.svg", box, 9);
        break;
    default:
        icon = nullptr;
        break;
    }
    icon->setSvgColor(Qt::yellow);
    icon->move(50, 50);
    box->setGeometry(0,0,800,800);
    return box;
}
WeatherPluginPrivate::WeatherPluginPrivate(WeatherPlugin *q)
    : q_ptr(q)
{}

WeatherPluginPrivate::~WeatherPluginPrivate() = default;


void WeatherPlugin::weatherUpdated(const WeatherData &weather)
{
    Q_D(WeatherPlugin);
    QGroupBox *box = qobject_cast<QGroupBox *>(d->m_exportedWidget);
    auto children = box->children();
    foreach(QObject *obj, children)
    {
        qDebug() << obj->metaObject()->className();
        if (obj->objectName() == d->m_weatherIconName)
        {
            WeatherIcon *icon = qobject_cast<WeatherIcon *>(obj);
            switch (weather.getWeatherOverview()) {
            case SUNNY:
            case RAINY:
            case CLOUDY:
            case WINDY:
            case SUNNY2RAINY:
            case SUNNY2CLOUDY:
            case CLOUDY2SUNNY:
            case RAINY2SUNNY:
                break;
            default:
                break;
            }
        }

    }
}


END_USER_NAMESPACE
