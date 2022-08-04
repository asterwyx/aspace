#include "pluginloader.h"
#include "plugininterface.h"
#include "pluginloader_p.h"
#include <QList>
#include <QWidget>
#include <QtGlobal>
#include <QApplication>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QPluginLoader>

namespace dspace {
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

bool PluginLoader::loadPlugins() {
    Q_D(PluginLoader);
    return d->loadPlugins();
}

void PluginLoader::showAllPlugins(QWidget *parent) {
    Q_D(PluginLoader);
    for (auto plugin : d->m_plugins) {
        QWidget *widget = plugin->pluginWidget("");
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
PluginLoaderPrivate::~PluginLoaderPrivate() = default;

bool PluginLoaderPrivate::loadPlugins() {
    qDebug() << "Enter load plugins.";
    QString appRunPrefix = qApp->applicationDirPath();
    foreach (QString pluginDir, m_pluginDirs)
    {
        QDir pluginsDir(appRunPrefix);
        pluginsDir.cdUp();
        pluginsDir.cd(pluginDir);
        foreach (QString fileName, pluginsDir.entryList(QDir::Files | QDir::Executable)) {
            qDebug() << fileName;
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
            QObject *plugin = pluginLoader.instance();
            PluginInterface *loadedInterface = qobject_cast<PluginInterface *>(plugin);
            if (loadedInterface) {
                qDebug() << "Load plugin" << plugin->metaObject()->className() << "successfully!";
                this->m_plugins.push_back(loadedInterface);
            }
        }
    }
    return true;
}
} // namespace dspace
