// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "pluginloader.h"
#include <QApplication>
#include <QMainWindow>

USE_USER_NAMESPACE

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QMainWindow w;
    PluginLoader loader("plugins/weather");
    // loader.addPluginDir("plugins/power");
    // loader.addPluginDir("plugins/echoeditor");
    loader.loadPlugins();
    loader.showAllPlugins(&w);
    w.resize(800, 800);
    w.show();
    return a.exec();
}
