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
#include "utils.h"

DCORE_USE_NAMESPACE

USE_USER_NAMESPACE

int main(int argc, char *argv[]) {
    DApplication a(argc, argv);
    Utils::registerAllMetaTypes();
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setStyle("chameleon");
    a.setProductIcon(QIcon::fromTheme("gnome-weather"));
    a.setWindowIcon(QIcon::fromTheme("gnome-weather"));
    MainWindow w;
    QPointer<QGSettings> settings(w.getWindowSettings());
    QScopedPointer<DConfig> config(DConfig::create("org.deepin.aspace", DCONFIG_FILE));
    PluginLoader loader(PLUGIN_DIR);
    QTimer::singleShot(0, &a, [&]{
        if(!config->isValid())
        {
            qWarning() << QString("DConfig is invalid, name:[%1], subpath[%2].").arg(config->name(), config->subpath());
            a.quit();
        }
        if (settings) {
            if (settings->get("first-run").toBool())
            {
                // First run select city
                QDialog dialog;
                dialog.setWindowTitle(QString::fromUtf8("初始化"));
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
                        settings->set("first-run", false);
                        dialog.close();
                    }
                });
                dialog.exec();
            }
        } else {
            a.quit();
        }
        if (config->value("locationId").toString().isEmpty())
        {
            a.quit();
        }
        loader.loadPlugins(&w);
        w.initializeAllPlugins();
        QtConcurrent::run([&]{
            w.loadData();
        });
        w.showSplash();
        w.show();
    });
    return a.exec();
}
