// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later
#include "mainwindow.h"
#include "pluginloader.h"
#include <DApplication>
#include "weatherdata.h"
#include <DConfig>
#include <QtConcurrent>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "weatherinterface.h"

DCORE_USE_NAMESPACE

USE_USER_NAMESPACE

int main(int argc, char *argv[]) {
    DApplication a(argc, argv);
    utils::registerAllMetaTypes();
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setStyle("chameleon");
    a.setProductIcon(QIcon::fromTheme("gnome-weather"));
    a.setWindowIcon(QIcon::fromTheme("gnome-weather"));
    MainWindow w;
    QPointer<QGSettings> settings(w.getWindowSettings());
    QScopedPointer<DConfig> config(DConfig::create("org.deepin.aspace", DCONFIG_FILE));
    if(!config->isValid())
    {
        qWarning() << QString("DConfig is invalid, name:[%1], subpath[%2].").arg(config->name(), config->subpath());
        return -1;
    }
    if (settings) {
        if (settings->get("first-run").toBool())
        {
            // First run select city
            settings->set("first-run", false);
            QDialog dialog;
            auto *lineEdit = new QLineEdit(&dialog);
            dialog.resize(300, 100);
            auto *label = new QLabel(QString::fromUtf8("请设置城市："), &dialog);
            label->setAlignment(Qt::AlignCenter);
            label->resize(100, 50);
            lineEdit->move(120, 5);
            lineEdit->resize(200 * 0.8, 50 * 0.8);
            auto *setButton = new QPushButton(QString::fromUtf8("设置"), &dialog);
            setButton->resize(300 * 0.8, 50 * 0.9);
            setButton->move(30, 55);
            QObject::connect(setButton, &QPushButton::clicked, &dialog, [&]()
            {
                WeatherInterface inter(DBUS_SERVICE_NAME, DBUS_ASPACE_PATH, QDBusConnection::sessionBus());
                QList<Location> locations = inter.lookForLocations(lineEdit->text());
                if (locations.isEmpty())
                {
                    QMessageBox::warning(nullptr, "查询错误", "查询不到相关城市");
                }
                else
                {
                    config->setValue("locationId", locations[0].id);
                    config->setValue("locationName", locations[0].name);
                    dialog.close();
                }
            });
            dialog.exec();
        }
    } else {
        exit(EXIT_FAILURE);
    }
    PluginLoader loader(PLUGIN_DIR);
    loader.loadPlugins(&w);
    w.initializeAllPlugins();
    QtConcurrent::run([&]{
        w.loadData();
    });
    w.showSplash();
    w.show();
    return a.exec();
}
