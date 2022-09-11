// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later
#include "mainwindow.h"
#include "pluginloader.h"
#include <DApplication>
#include "weatherdata.h"


USE_USER_NAMESPACE

int main(int argc, char *argv[]) {
    DApplication a(argc, argv);
    utils::registerAllMetaTypes();
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setStyle("chameleon");
    a.setProductIcon(QIcon::fromTheme("gnome-weather"));
    a.setWindowIcon(QIcon::fromTheme("gnome-weather"));
    MainWindow w;
    w.loadDefaultSize();
    PluginLoader loader;
    loader.loadPlugins(&w);
    // Use GSettings to save default size.
    w.initializeAllPlugins();
    w.dumpObjectTree();
    w.show();
    return a.exec();
}
