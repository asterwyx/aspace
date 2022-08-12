// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "plugininterface.h"
#include <QWidget>
#include <QScopedPointer>
#include <QDBusMessage>

#include "global.h"
#include "weatherdata.h"

BEGIN_USER_NAMESPACE
class WeatherPluginPrivate;
class WeatherPlugin : public QObject, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_INTERFACE_ID)
    Q_INTERFACES(PluginInterface)
public:
    WeatherPlugin();
    ~WeatherPlugin() override;
    QString pluginName() const override;
    QString pluginDisplayName() const override;
    QWidget *pluginWidget(const QString &key) override;
private slots:
    void weatherUpdated(QDBusMessage weatherMsg);
    void onWeatherChanged(const WeatherData &weather);
private:
    Q_DECLARE_PRIVATE(WeatherPlugin)
    QScopedPointer<WeatherPluginPrivate> d_ptr;
};

END_USER_NAMESPACE

