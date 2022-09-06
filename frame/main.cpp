// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later
#include "mainwindow.h"
#include "pluginloader.h"
#include <QApplication>
#include "weatherdata.h"


USE_USER_NAMESPACE

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    utils::registerAllMetaTypes();
    MainWindow w;
    QIcon applicationIcon = QIcon::fromTheme("gnome-weather", QIcon(":/icons/gnome-weather.svg"));
    w.setWindowIcon(applicationIcon);
    PluginLoader loader(PLUGIN_DIR);
    loader.loadPlugins();
    loader.showAllPlugins(&w);
    // Use GSettings to save default size.
    w.loadDefaultSize();
    w.show();
    return a.exec();
}
