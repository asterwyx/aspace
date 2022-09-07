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

BEGIN_USER_NAMESPACE
PluginLoader::PluginLoader(const QString &pluginDir)
    : d_ptr(new PluginLoaderPrivate(this)) {
    Q_D(PluginLoader);
    d->m_pluginDirs.push_back(pluginDir);
}

PluginLoader::PluginLoader(const QString &pluginDir, PluginLoaderPrivate &dd)
    : d_ptr(&dd) {
    Q_D(PluginLoader);
    d->m_pluginDirs.push_back(pluginDir);
}

PluginLoader::~PluginLoader() = default;

bool PluginLoader::loadPlugins(FrameProxyInterface *proxy) {
    Q_D(PluginLoader);
    return d->loadPlugins(proxy);
}

void PluginLoader::showAllPlugins(QWidget *parent) {
    Q_D(PluginLoader);
    foreach (PluginInterface *plugin, d->m_plugins) {
        QWidget *widget = plugin->pluginItemWidget("");
        widget->setParent(parent);
    }
}

PluginLoader::PluginLoader() : d_ptr(new PluginLoaderPrivate(this)){}

void PluginLoader::addPluginDir(QString pluginDir) {
    Q_D(PluginLoader);
    d->m_pluginDirs.push_back(pluginDir);
}

const QList<PluginInterface *> *PluginLoader::getPlugins()
{
    Q_D(PluginLoader);
    return &d->m_plugins;
}

PluginLoaderPrivate::PluginLoaderPrivate(PluginLoader *q) : q_ptr(q) {}
PluginLoaderPrivate::~PluginLoaderPrivate()
{
    foreach (PluginInterface* plugin, m_plugins) {
        delete plugin;
    }
}

bool PluginLoaderPrivate::loadPlugins(FrameProxyInterface *proxy) {
    QString appRunPrefix = qApp->applicationDirPath();
    foreach (QString pluginDir, m_pluginDirs)
    {
        QDir pluginsDir(appRunPrefix);
        if (pluginDir.startsWith('/'))
        {
            // absolute path
            pluginsDir = QDir(pluginDir); 
        }
        {
            pluginsDir.cd(pluginDir);
        }
        foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
            
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
            QObject *plugin = pluginLoader.instance();
            PluginInterface *loadedPlugin = qobject_cast<PluginInterface *>(plugin);
            if (loadedPlugin) {
                qDebug() << "Load plugin" << plugin->metaObject()->className() << "successfully!";
                proxy->addPlugin(loadedPlugin);
                this->m_plugins.push_back(loadedPlugin);
            }
        }
    }
    return true;
}
END_USER_NAMESPACE
