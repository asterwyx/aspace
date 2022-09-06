// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "plugininterface.h"
#include <QWidget>
#include <QLabel>
#include <QScopedPointer>
#include <QDBusMessage>

#include "common_def.h"
#include "weatherdata.h"
#include "weathericon.h"
#include "weathercontroller.h"
#include "locationselector.h"

BEGIN_USER_NAMESPACE
class WeatherPluginPrivate;
class WeatherPlugin : public QObject, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_INTERFACE_IID)
    Q_INTERFACES(USER_NAMESPACE::PluginInterface)
public:
    Q_PROPERTY(int temperatureFontPointSize MEMBER m_temperatureFontPointSize NOTIFY temperatureFontPointSizeChanged)
    Q_PROPERTY(int temperatureFontWeight MEMBER m_temperatureFontWeight NOTIFY temperatureFontWeightChanged)
    Q_PROPERTY(QString temperatureFontFamily MEMBER m_temperatureFontFamily NOTIFY temperatureFontFamilyChanged)
    Q_PROPERTY(int currentWeatherWidth MEMBER m_currentWeatherWidth NOTIFY currentWeatherWidthChanged)
    Q_PROPERTY(int currentWeatherHeight MEMBER m_currentWeatherHeight NOTIFY currentWeatherHeightChanged)

public:
    static const QString CURRENT_WEATHER_ITEM;

public:
    WeatherPlugin(FrameProxyInterface *frameProxy = nullptr, QObject *parent = nullptr);
    ~WeatherPlugin() override;
    QString pluginName() const override;
    QString pluginDisplayName() const override;
    QWidget *pluginItemWidget(const QString &key) override;
    
    void preInitialize() override;
    void initialize() override;
    void adjustSize(QResizeEvent *event, const QMap<QString, QWidget *> &items) override;

signals:
    void temperatureFontPointSizeChanged(int fontPointSize);
    void temperatureFontWeightChanged(int fontWeight);
    void temperatureFontFamilyChanged(QString fontFamily);
    void currentWeatherWidthChanged(int currentWidth);
    void currentWeatherHeightChanged(int currentHeight);

private slots:
    void onCurrentWeatherChanged(const CurrentWeather &weather);
private:
    QWidget                             *m_currentWeatherWidget;
    WeatherIcon                         *m_weatherIcon;
    QLabel                              *m_temperatureLabel;
    LocationSelector                    *m_locationSelector;
    int                                 m_temperatureFontPointSize;
    int                                 m_temperatureFontWeight;
    QString                             m_temperatureFontFamily;
    int                                 m_currentWeatherWidth;
    int                                 m_currentWeatherHeight;
    QSize                               m_size;
    QScopedPointer<WeatherController>   m_controller;
    QSharedPointer<WeatherModel>        m_model;
};

END_USER_NAMESPACE

