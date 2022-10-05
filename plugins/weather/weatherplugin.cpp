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
#include "controllers/listwidgetdelegate.h"
#include <DConfig>

DCORE_USE_NAMESPACE
BEGIN_USER_NAMESPACE

const QString WeatherPlugin::CURRENT_WEATHER_ITEM = "current-weather";
const QString WeatherPlugin::FUTURE_WEATHER_ITEM = "future-weather";

WeatherPlugin::WeatherPlugin(FrameProxyInterface *frameProxy, QObject *parent)
    : QObject(parent)
    , PluginInterface(frameProxy)
    , m_currentWeatherWidget(new QGroupBox)
    , m_weatherIcon(new WeatherIcon)
    , m_temperatureLabel(new QLabel)
    , m_locationLabel(new QLabel)
    , m_updateTime(new QLabel)
    , m_feelLikeLabel(new QLabel)
    , m_futureWeatherList(new ListView)
    , m_controller(new WeatherController)
    , m_currentWeatherModel(m_controller->getCurrentWeatherModel())
    , m_futureWeatherModel(m_controller->getFutureWeatherModel())
{
}

WeatherPlugin::~WeatherPlugin() = default;

QString WeatherPlugin::pluginName() const
{
    return {"aspace-weather"};
}
QString WeatherPlugin::pluginDisplayName() const
{
    return {"Weather"};
}

void WeatherPlugin::initialize()
{
    // initialize will initialize ui elements
    FrameProxyInterface *proxy = frameProxy();
    if (!proxy) {
        qWarning() << "Please set frame proxy of WeatherPlugin" << this;
        return;
    }
    int currentWeatherWidth = 3 * LIST_WIDGET_WIDTH + 2 * LISTVIEW_ITEM_SPACING;
    int currentWeatherHeight = LIST_WIDGET_WIDTH;
    QFont labelFont("Noto Sans CJK SC");
    labelFont.setWeight(100);
    labelFont.setPointSize(36);
    m_currentWeatherWidget->setFixedSize(currentWeatherWidth, currentWeatherHeight);
    m_weatherIcon->setParent(m_currentWeatherWidget);
    m_weatherIcon->setColor(Qt::yellow);
    m_weatherIcon->resize(currentWeatherHeight * 0.8, currentWeatherHeight * 0.8);
    m_weatherIcon->move(currentWeatherHeight * 0.1, currentWeatherHeight * 0.1);
    m_temperatureLabel->setParent(m_currentWeatherWidget);
    m_temperatureLabel->setFont(labelFont);
    m_temperatureLabel->resize((currentWeatherWidth - currentWeatherHeight) / 2, currentWeatherHeight / 3 * 2);
    m_temperatureLabel->move(currentWeatherHeight, currentWeatherHeight / 3);
    m_locationLabel->setParent(m_currentWeatherWidget);
    QFont locationFont("Noto Sans CJK SC");
    locationFont.setWeight(100);
    locationFont.setPointSize(16);
    m_locationLabel->setFont(locationFont);
    m_locationLabel->move(currentWeatherHeight, 0);
    m_locationLabel->resize((currentWeatherWidth - currentWeatherHeight) / 4, currentWeatherHeight / 3);
    m_updateTime->setParent(m_currentWeatherWidget);
    // m_updateTime->setFont(locationFont);
    m_updateTime->move((currentWeatherWidth + 3 * currentWeatherHeight) / 4, 0);
    m_updateTime->resize((currentWeatherWidth - currentWeatherHeight) / 4 * 3, currentWeatherHeight / 3);
    m_feelLikeLabel->setParent(m_currentWeatherWidget);
    m_feelLikeLabel->setFont(locationFont);
    m_feelLikeLabel->move((currentWeatherWidth + currentWeatherHeight) / 2, currentWeatherHeight / 2);
    m_feelLikeLabel->resize((currentWeatherWidth - currentWeatherHeight) / 2, currentWeatherHeight / 2);
    m_futureWeatherList->setModel(m_futureWeatherModel.data());
    m_futureWeatherModel->setList(m_futureWeatherList);
    m_futureWeatherList->setItemDelegate(new ListWidgetDelegate(this));
    QScopedPointer<DConfig> config(DConfig::create("org.deepin.aspace", DCONFIG_FILE));
    Location location;
    location.id = config->value("locationId").toString();
    location.name = config->value("locationName").toString();
    m_controller->setLocation(location);
    connect(m_futureWeatherModel.data(),
            &FutureWeatherModel::dataChanged,
            m_futureWeatherList,
            static_cast<void (ListView::*)()>(&ListView::update));
    connect(
        m_currentWeatherModel.data(), &CurrentWeatherModel::currentWeatherChanged, this, &WeatherPlugin::onCurrentWeatherChanged);
    proxy->addItem(this, CURRENT_WEATHER_ITEM);
    proxy->addItem(this, FUTURE_WEATHER_ITEM);
}

void WeatherPlugin::loadData()
{
    // Here we might do IO and initialize data
    // Only configuration value is correct, we have a right location info,
    // do we load weather plugin. That is, in this function, we may confirm that
    // we can get a correct location info from configuration, do not need to query
    // from the internet.
    m_controller->updateCurrentWeather();
    m_controller->updateFutureWeather();
}

QWidget *WeatherPlugin::pluginItemWidget(const QString &key)
{
    if (key == CURRENT_WEATHER_ITEM) {
        return this->m_currentWeatherWidget;
    } else if (key == FUTURE_WEATHER_ITEM) {
        return this->m_futureWeatherList;
    } else {
        return nullptr;
    }
}

void WeatherPlugin::onCurrentWeatherChanged(const CurrentWeather &weather)
{
    qDebug() << "weather changed, slot triggered.";
    // Change weather icon by name
    QSize origin = m_weatherIcon->size();  // Keep original size
    m_weatherIcon->setIconFromName(weather.iconName);
    m_weatherIcon->setScaleFactor(qMin(origin.width(), origin.height()) / static_cast<double>(m_weatherIcon->size().width()));
    m_weatherIcon->resize(origin);
    // Set temperature text
    QString temperatureStr = QString::number(weather.temperature, 10, 0);
    temperatureStr += "\u00B0";
    if (weather.temperatureUnit == TemperatureUnit::CELSIUS) {
        temperatureStr += "C";
    } else {
        temperatureStr += "F";
    }
    m_temperatureLabel->setText(temperatureStr);
    // Set location selector text
    m_locationLabel->setText(m_controller->getLocationModel()->getLocation().name);
    m_feelLikeLabel->setText(QString::fromUtf8("体感温度：%1°").arg(weather.feelsLikeTemperature));
    m_updateTime->setText(QString::fromUtf8("更新时间：%1").arg(m_controller->getUpdateTime().toString()));
}

void WeatherPlugin::adjustSize(QResizeEvent *event, const QMap<QString, QWidget *> &items)
{
    Q_UNUSED(event)
    Q_UNUSED(items)
}

END_USER_NAMESPACE
