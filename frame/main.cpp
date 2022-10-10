// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later
#include "mainwindow.h"
#include "pluginloader.h"
#include <DApplication>
#include <DConfig>
#include <QtConcurrent>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "utils.h"
#include "contentpage.h"

DCORE_USE_NAMESPACE
USE_USER_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    Utils::registerAllMetaTypes();
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setStyle("chameleon");
    a.setProductIcon(QIcon::fromTheme("gnome-weather"));
    a.setWindowIcon(QIcon::fromTheme("gnome-weather"));
    MainWindow w;
    auto settings = w.getWindowSettings();
    auto config = w.getDConfig();
#if defined(PORTABLE)
    PluginLoader loader("./plugins/all");
#else
    PluginLoader loader(PLUGIN_DIR);
#endif
    QTimer::singleShot(0, [&] {
        if (!config->isValid()) {
            qWarning() << QString("DConfig is invalid, name:[%1], subpath[%2].").arg(config->name(), config->subpath());
            a.quit();
        }
        if (settings) {
            if (settings->get("first-run").toBool()) {
                w.showSelect();
            } else {
                if (config->value("locationId").toString().isEmpty()) {
                    config->reset("locationId");
                    config->reset("locationName");
                    settings->set("first-run", true);
                    w.showSelect();
                } else {
                    w.showContents();
                }
            }
        } else {
            qCritical() << "Invalid GSetting pointer!";
            a.quit();
        }
    });
    loader.loadPlugins(w.getContentPage().data());
    w.getContentPage()->initializeAllPlugins();
    w.showSplash();
    w.show();
    return a.exec();
}
