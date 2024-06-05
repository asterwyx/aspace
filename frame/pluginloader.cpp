// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "pluginloader.h"
#include "plugininterface.h"
#include "pluginloader_p.h"
#include <QList>
#include <QWidget>
#include <QtGlobal>
#include <QApplication>
#include <QDir>
#include <QString>
#include <QPluginLoader>


PluginLoader::PluginLoader(const QString &pluginDir)
    : d_ptr(new PluginLoaderPrivate(this))
{
    Q_D(PluginLoader);
    d->m_pluginDirs.append(pluginDir);
}

PluginLoader::~PluginLoader() = default;

bool PluginLoader::loadPlugins(FrameProxyInterface *proxy)
{
    Q_D(PluginLoader);
    return d->loadPlugins(proxy);
}

PluginLoader::PluginLoader()
    : d_ptr(new PluginLoaderPrivate(this))
{
}

void PluginLoader::addPluginDir(QString pluginDir)
{
    Q_D(PluginLoader);
    if (!pluginDir.isEmpty())
        d->m_pluginDirs.append(pluginDir);
}

const QList<PluginInterface *> *PluginLoader::getPlugins()
{
    Q_D(PluginLoader);
    return &d->m_plugins;
}

PluginLoaderPrivate::PluginLoaderPrivate(PluginLoader *q)
    : q_ptr(q)
{
}
PluginLoaderPrivate::~PluginLoaderPrivate()
{
    foreach (PluginInterface *plugin, m_plugins) {
        delete plugin;
    }
}

bool PluginLoaderPrivate::loadPlugins(FrameProxyInterface *proxy)
{
    QString appRunPrefix = qApp->applicationDirPath();
    foreach (QString pluginDir, m_pluginDirs) {
        QDir pluginsDir(appRunPrefix);
        pluginsDir.cd(pluginDir);
        foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
            QObject *plugin = pluginLoader.instance();
            PluginInterface *loadedPlugin = qobject_cast<PluginInterface *>(plugin);
            if (loadedPlugin) {
                qDebug() << "Load plugin" << plugin->metaObject()->className() << "successfully!";
                if (proxy) {
                    proxy->addPlugin(loadedPlugin);
                }
                this->m_plugins.push_back(loadedPlugin);
            }
        }
    }
    return true;
}
