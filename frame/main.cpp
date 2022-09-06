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
    w.loadDefaultSize();
    PluginLoader loader(PLUGIN_DIR);
    loader.loadPlugins(&w);
    w.initializeAllPlugins();
    // Use GSettings to save default size.
    w.dumpObjectTree();
    w.show();
    return a.exec();
}
