// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "pluginloader.h"
#include <QApplication>
#include <QMainWindow>
#include "weatherdata.h"

USE_USER_NAMESPACE

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    WeatherData::registerMetaTypes();
    QMainWindow w;
    QIcon applicationIcon = QIcon::fromTheme("gnome-weather", QIcon(":/icons/gnome-weather.svg"));
    w.setWindowIcon(applicationIcon);
    PluginLoader loader(PLUGIN_DIR);
    loader.loadPlugins();
    loader.showAllPlugins(&w);
    w.resize(800, 800);
    w.show();
    return a.exec();
}
