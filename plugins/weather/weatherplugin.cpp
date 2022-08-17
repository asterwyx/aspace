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
#include <QPushButton>
#include <QtConcurrent>

#include "weatherdata.h"
#include "weathericon.h"
#include "weatherinterface.h"

BEGIN_USER_NAMESPACE

WeatherPlugin::WeatherPlugin() : d_ptr(new WeatherPluginPrivate(this)) {}
WeatherPlugin::~WeatherPlugin() = default;

QString WeatherPlugin::pluginName() const { return {"aspace-weather"}; }
QString WeatherPlugin::pluginDisplayName() const { return {"Weather"}; }

QWidget *WeatherPlugin::pluginWidget(const QString &key) {
    Q_UNUSED(key)
    Q_D(WeatherPlugin);
    // just create widget, data is updated with callback.
    QFont labelFont("Noto Sans CJK SC");
    labelFont.setWeight(100);
    labelFont.setPointSize(16);
    QGroupBox *box = new QGroupBox();
    d->m_exportedWidget = box;
    box->resize(d->m_size);
    box->setObjectName("WeatherPluginWidget");
    QLabel* temperLabel = new QLabel(box);
    temperLabel->setObjectName(d->m_temperatureLabelName);
    temperLabel->setFont(labelFont);
    temperLabel->resize(d->m_size.width() / 2, d->m_size.height() / 3);
    temperLabel->move(0, d->m_size.height() / 3);
    QLabel* locationLabel = new QLabel(box);
    locationLabel->setObjectName(d->m_locationLabelName);
    locationLabel->setFont(labelFont);
    locationLabel->resize(d->m_size.width() / 2, d->m_size.height() / 3);
    QPushButton *updateButton = new QPushButton(box);
    updateButton->setText(tr("更新天气"));
    connect(updateButton, &QPushButton::clicked, this, [=](bool checked)
    {   
        Q_UNUSED(checked)
        QtConcurrent::run([=] {
            QDBusConnection bus = QDBusConnection::sessionBus();
            WeatherInterface weatherInterface(DBUS_SERVICE_NAME, DBUS_ASPACE_PATH, bus);
            QDBusPendingReply<WeatherData> reply = weatherInterface.getCurrentWeather();
            reply.waitForFinished();
            if (reply.isError())
            {
                qWarning() << reply.error().message();
            }
            else
            {
                onWeatherChanged(reply.value());
            }
        });

    });
    updateButton->move(0, d->m_size.height() / 3 * 2);
    WeatherIcon *icon = new WeatherIcon("", box);
    icon->setObjectName(d->m_weatherIconName);
    icon->setSvgColor(Qt::yellow);
    icon->move(d->m_size.width() / 2, 0);
    icon->resize(d->m_size / 2);
    return box;
}
WeatherPluginPrivate::WeatherPluginPrivate(WeatherPlugin *q)
    : q_ptr(q),
    m_exportedWidget(nullptr),
    m_weatherIconName("WeatherPluginWidget::WeatherIcon"),
    m_locationLabelName("WeatherPluginWidget::LocationLabel"),
    m_temperatureLabelName("WeatherPluginWidget::TemperatureLabel"),
    m_size(400, 200)
{

}

WeatherPluginPrivate::~WeatherPluginPrivate() = default;


void WeatherPlugin::onWeatherChanged(const WeatherData &weather)
{
    qDebug() << "weather changed, slot triggered.";
    Q_D(WeatherPlugin);
    QGroupBox *box = qobject_cast<QGroupBox *>(d->m_exportedWidget);
    QObjectList children = box->children();
    foreach(QObject *obj, children)
    {
        if (obj->objectName() == d->m_weatherIconName)
        {
            // weather icon
            WeatherIcon *icon = qobject_cast<WeatherIcon *>(obj);
            switch (weather.overview) {
            case SUNNY:
                icon->setIcon(":/icons/sunny.svg");
                break;
            case RAINY:
                icon->setIcon(":/icons/slightly_rainy.svg");
                break;
            case CLOUDY:
            case WINDY:
            case SUNNY2RAINY:
            case SUNNY2CLOUDY:
            case CLOUDY2SUNNY:
            case RAINY2SUNNY:
            default:
                break;
            }
        }
        else if (obj->objectName() == d->m_locationLabelName)
        {
            // location label
            QLabel *locationLabel = qobject_cast<QLabel *>(obj);
            locationLabel->setText(weather.location);
        }
        else if (obj->objectName() == d->m_temperatureLabelName)
        {
            // temperature label
            QLabel *temperatureLabel = qobject_cast<QLabel *>(obj);
            QString temperatureStr = QString::number(weather.currentTemperature, 10, 0);
            temperatureStr += "\u00B0";
            if (weather.unit == TemperatureUnit::CELSIUS)
            {
                temperatureStr += "C";
            }
            else
            {
                temperatureStr += "F";
            }
            temperatureLabel->setText(temperatureStr);
        }
    }
}

void WeatherPlugin::weatherUpdated(QDBusMessage weatherMsg)
{
    qDebug() << "weather updated.";
    WeatherData weather;
    if (weatherMsg.type() == QDBusMessage::ErrorMessage)
    {
        qWarning() << "can't get weather, get a error a message.";
        return;
    }
    else if (weatherMsg.type() == QDBusMessage::ReplyMessage)
    {
        QList<QVariant> arguments = weatherMsg.arguments();
        weather = qdbus_cast<WeatherData>(arguments.takeFirst());
        onWeatherChanged(weather);
    }
    else
    {
        qWarning() << "unknown message type.";
        return;
    }
    
}
END_USER_NAMESPACE
