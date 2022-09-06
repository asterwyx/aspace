// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "weatherplugin.h"
#include <QLabel>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QGroupBox>
#include <QFont>
#include <QDebug>
#include <QDBusArgument>
#include <QPushButton>
#include <QtConcurrent>

#include "frameproxyinterface.h"
#include "weatherdata.h"
#include "weathericon.h"


BEGIN_USER_NAMESPACE


const QString WeatherPlugin::CURRENT_WEATHER_ITEM =  "current-weather";

WeatherPlugin::WeatherPlugin(FrameProxyInterface *frameProxy, QObject *parent)
    : QObject(parent), PluginInterface(frameProxy),
    m_currentWeatherWidget(nullptr), m_size(0, 0)
{
    if (this->frameProxy())
    {
        m_size = this->frameProxy()->getSize();
    }
}

WeatherPlugin::~WeatherPlugin() = default;

QString WeatherPlugin::pluginName() const { return {"aspace-weather"}; }
QString WeatherPlugin::pluginDisplayName() const { return {"Weather"}; }

void WeatherPlugin::preInitialize(FrameProxyInterface *proxy)
{
    if (!proxy)
        proxy = frameProxy();
    this->setProperty("temperatureFontPointSize", 36);
    this->setProperty("temperatureFontWeight", 100);
    this->setProperty("temperatureFontFamily", "Noto Sans CJK SC");
    this->setProperty("currentWeatherWidth", proxy->getSize().width());
    this->setProperty("currentWeatherHeight", 100);
}

void WeatherPlugin::initialize(FrameProxyInterface *proxy)
{
    if (!proxy)
        proxy = frameProxy();
    int currentWeatherWidth = this->property("currentWeatherWidth").toInt();
    int currentWeatherHeight = this->property("currentWeatherHeight").toInt();    
    QFont labelFont(this->property("temperatureFontFamily").toString());
    labelFont.setWeight(this->property("temperatureFontWeight").toInt());
    labelFont.setPointSize(this->property("temperatureFontPointSize").toInt());
    m_currentWeatherWidget = new QGroupBox;
    m_currentWeatherWidget->resize(currentWeatherWidth, currentWeatherHeight);
    m_weatherIcon = new WeatherIcon();
    m_weatherIcon->setParent(m_currentWeatherWidget);
    m_weatherIcon->resize(currentWeatherHeight, currentWeatherHeight);
    m_temperatureLabel = new QLabel();
    m_temperatureLabel->setParent(m_currentWeatherWidget);
    m_temperatureLabel->setFont(labelFont);
    m_temperatureLabel->resize(currentWeatherWidth - currentWeatherHeight, currentWeatherHeight / 3.0 * 2.0);
    m_temperatureLabel->move(currentWeatherHeight, currentWeatherHeight / 3);
    m_locationSelector = new LocationSelector(m_currentWeatherWidget);
    m_locationSelector->resize(currentWeatherWidth - currentWeatherHeight, currentWeatherHeight / 3);
    m_locationSelector->move(currentWeatherHeight, 0);
    m_model = new WeatherModel(this);
}

QWidget *WeatherPlugin::pluginItemWidget(const QString &key) {
    if (key == CURRENT_WEATHER_ITEM)
    {
        return this->m_currentWeatherWidget;
    }
    else
    {
        return nullptr;
    }
    
    // Q_UNUSED(key)
    // Q_D(WeatherPlugin);
    // // just create widget, data is updated with callback.
    // QFont labelFont("Noto Sans CJK SC");
    // labelFont.setWeight(100);
    // labelFont.setPointSize(16);
    // QGroupBox *box = new QGroupBox();
    // d->m_exportedWidget = box;
    // box->resize(d->m_size);
    // box->setObjectName("WeatherPluginWidget");
    // QLabel* temperLabel = new QLabel(box);
    // temperLabel->setObjectName(d->m_temperatureLabelName);
    // temperLabel->setFont(labelFont);
    // temperLabel->resize(d->m_size.width() / 2, d->m_size.height() / 3);
    // temperLabel->move(0, d->m_size.height() / 3);
    // QLabel* locationLabel = new QLabel(box);
    // locationLabel->setObjectName(d->m_locationLabelName);
    // locationLabel->setFont(labelFont);
    // locationLabel->resize(d->m_size.width() / 2, d->m_size.height() / 3);
    // QPushButton *updateButton = new QPushButton(box);
    // updateButton->setText(tr("更新天气"));
    // connect(updateButton, &QPushButton::clicked, this, [=](bool checked)
    // {   
    //     Q_UNUSED(checked)
    //     QtConcurrent::run([=] {
    //         QDBusConnection bus = QDBusConnection::sessionBus();
    //         WeatherInterface weatherInterface(DBUS_SERVICE_NAME, DBUS_ASPACE_PATH, bus);
    //         QDBusPendingReply<CurrentWeather> reply = weatherInterface.getCurrentWeather();
    //         reply.waitForFinished();
    //         if (reply.isError())
    //         {
    //             qWarning() << reply.error().message();
    //         }
    //         else
    //         {
    //             onWeatherChanged(reply.value());
    //         }
    //     });

    // });
    // updateButton->move(0, d->m_size.height() / 3 * 2);
    // WeatherIcon *icon = new WeatherIcon;
    // icon->setParent(box);
    // icon->setObjectName(d->m_weatherIconName);
    // icon->setColor(Qt::yellow);
    // icon->move(d->m_size.width() / 2, 0);
    // icon->resize(d->m_size.width() / 2, d->m_size.height());
    // return ;
}

// void WeatherPlugin::onWeatherChanged(const CurrentWeather &weather)
// {
//     qDebug() << "weather changed, slot triggered.";
//     Q_D(WeatherPlugin);
//     QGroupBox *box = qobject_cast<QGroupBox *>(d->m_exportedWidget);
//     QObjectList children = box->children();
//     foreach(QObject *obj, children)
//     {
//         if (obj->objectName() == d->m_weatherIconName)
//         {
//             // weather icon
//             WeatherIcon *icon = qobject_cast<WeatherIcon *>(obj);
//             QSize origin = icon->size();
//             icon->setIconFromName(weather.iconName);
//             icon->setScaleFactor(qMin(origin.width(), origin.height()) / static_cast<double>(icon->size().width()));
//         }
//         else if (obj->objectName() == d->m_locationLabelName)
//         {
//             // location label
//             QLabel *locationLabel = qobject_cast<QLabel *>(obj);
//             locationLabel->setText(weather.location.name);
//         }
//         else if (obj->objectName() == d->m_temperatureLabelName)
//         {
//             // temperature label
//             QLabel *temperatureLabel = qobject_cast<QLabel *>(obj);
//             QString temperatureStr = QString::number(weather.temperature, 10, 0);
//             temperatureStr += "\u00B0";
//             if (weather.temperatureUnit == TemperatureUnit::CELSIUS)
//             {
//                 temperatureStr += "C";
//             }
//             else
//             {
//                 temperatureStr += "F";
//             }
//             temperatureLabel->setText(temperatureStr);
//         }
//     }
// }

void WeatherPlugin::weatherUpdated(QDBusMessage weatherMsg)
{
    qDebug() << "weather updated.";
    CurrentWeather weather;
    if (weatherMsg.type() == QDBusMessage::ErrorMessage)
    {
        qWarning() << "can't get weather, get a error a message.";
        return;
    }
    else if (weatherMsg.type() == QDBusMessage::ReplyMessage)
    {
        QList<QVariant> arguments = weatherMsg.arguments();
        weather = qdbus_cast<CurrentWeather>(arguments.takeFirst());
        onWeatherChanged(weather);
    }
    else
    {
        qWarning() << "unknown message type.";
        return;
    }
}
END_USER_NAMESPACE
