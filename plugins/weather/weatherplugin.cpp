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
#include <QListView>

#include "frameproxyinterface.h"
#include "weatherdata.h"
#include "weathericon.h"


BEGIN_USER_NAMESPACE


const QString WeatherPlugin::CURRENT_WEATHER_ITEM =  "current-weather";
const QString WeatherPlugin::FUTURE_WEATHER_ITEM = "future-weather";

WeatherPlugin::WeatherPlugin(FrameProxyInterface *frameProxy, QObject *parent)
    : QObject(parent), PluginInterface(frameProxy),
    m_currentWeatherWidget(nullptr),
    m_size(0, 0),
    m_controller(new WeatherController),
    m_model(m_controller->getWeatherModel())
{
    if (this->frameProxy())
    {
        m_size = this->frameProxy()->getFrameSize();
    }
}

WeatherPlugin::~WeatherPlugin() = default;

QString WeatherPlugin::pluginName() const { return {"aspace-weather"}; }
QString WeatherPlugin::pluginDisplayName() const { return {"Weather"}; }

void WeatherPlugin::preInitialize()
{
    FrameProxyInterface *proxy = frameProxy();
    if (!proxy)
    {
        qWarning() << "Please set frame proxy for WeatherPlugin" << this;
        return;
    }
    this->setProperty("temperatureFontPointSize", 36);
    this->setProperty("temperatureFontWeight", 100);
    this->setProperty("temperatureFontFamily", "Noto Sans CJK SC");
    this->setProperty("currentWeatherWidth", proxy->getFrameSize().width());
    this->setProperty("currentWeatherHeight", 100);
}

void WeatherPlugin::initialize()
{
    FrameProxyInterface *proxy = frameProxy();
    if (!proxy)
    {
        qWarning() << "Please set frame proxy of WeatherPlugin" << this;
        return;
    }
    int currentWeatherWidth = this->property("currentWeatherWidth").toInt();
    int currentWeatherHeight = this->property("currentWeatherHeight").toInt();    
    QFont labelFont(this->property("temperatureFontFamily").toString());
    labelFont.setWeight(this->property("temperatureFontWeight").toInt());
    labelFont.setPointSize(this->property("temperatureFontPointSize").toInt());
    m_currentWeatherWidget = new QGroupBox;
    m_currentWeatherWidget->resize(currentWeatherWidth, currentWeatherHeight);
    m_weatherIcon = new WeatherIcon();
    m_weatherIcon->setParent(m_currentWeatherWidget);
    m_weatherIcon->setColor(Qt::yellow);
    m_weatherIcon->resize(currentWeatherHeight, currentWeatherHeight);
    m_temperatureLabel = new QLabel();
    m_temperatureLabel->setParent(m_currentWeatherWidget);
    m_temperatureLabel->setFont(labelFont);
    m_temperatureLabel->resize(currentWeatherWidth - currentWeatherHeight, currentWeatherHeight / 3.0 * 2.0);
    m_temperatureLabel->move(currentWeatherHeight, currentWeatherHeight / 3);
    m_locationSelector = new LocationSelector(m_currentWeatherWidget);
    m_locationSelector->resize(currentWeatherWidth - currentWeatherHeight, currentWeatherHeight / 3);
    m_locationSelector->move(currentWeatherHeight, 0);
    m_controller->updateCurrentWeather();
    connect(m_model.data(), &WeatherModel::currentWeatherChanged, this, &WeatherPlugin::onCurrentWeatherChanged);
    proxy->addItem(this, CURRENT_WEATHER_ITEM);
}

QWidget *WeatherPlugin::pluginItemWidget(const QString &key) {
    if (key == CURRENT_WEATHER_ITEM)
    {
        return this->m_currentWeatherWidget;
    }
    else if (key == FUTURE_WEATHER_ITEM)
    {
        return new QLabel;
    }
    else
    {
        return nullptr;
    }
}

void WeatherPlugin::onCurrentWeatherChanged(const CurrentWeather &weather)
{
    qDebug() << "weather changed, slot triggered.";
    QGroupBox *box = qobject_cast<QGroupBox *>(m_currentWeatherWidget);
    QObjectList children = box->children();
    // Change weather icon by name
    QSize origin = m_weatherIcon->size(); // Keep original size
    m_weatherIcon->setIconFromName(weather.iconName);
    m_weatherIcon->setScaleFactor(qMin(origin.width(), origin.height()) / static_cast<double>(m_weatherIcon->size().width()));
    // Set temperature text
    QString temperatureStr = QString::number(weather.temperature, 10, 0);
    temperatureStr += "\u00B0";
    if (weather.temperatureUnit == TemperatureUnit::CELSIUS)
    {
        temperatureStr += "C";
    }
    else
    {
        temperatureStr += "F";
    }
    m_temperatureLabel->setText(temperatureStr);
    // Set location selector text
}

void WeatherPlugin::adjustSize(QResizeEvent *event, const QMap<QString, QWidget *> &items) {
    QWidget *currentWeatherWidget = items[CURRENT_WEATHER_ITEM];
}


END_USER_NAMESPACE
