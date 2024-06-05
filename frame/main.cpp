// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later
#include "mainwindow.h"
#include "pluginloader.h"
#include <QApplication>
#include <DConfig>
#include <QtConcurrent>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "utils.h"
#include "contentpage.h"
#include "settings.h"

DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Utils::registerAllMetaTypes();
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setStyle("chameleon");
    a.setWindowIcon(QIcon::fromTheme("gnome-weather"));
    MainWindow w;
    auto settings = Settings::applicationSettings();
#if defined(PORTABLE)
    PluginLoader loader("./plugins/all");
#else
    PluginLoader loader(PLUGIN_DIR);
#endif
    QTimer::singleShot(0, [&] {

        if (settings) {
            if (settings->get("first-run").toBool()) {
                w.showSelect();
            } else {
                if (settings->get("locationId").toString().isEmpty()) {
                    settings->reset("locationId");
                    settings->reset("locationName");
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
