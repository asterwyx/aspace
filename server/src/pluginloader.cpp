#include "pluginloader.h"
#include "plugininterface.h"
#include "pluginloader_p.h"
#include <QList>
#include <QWidget>
#include <QtGlobal>

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
} // namespace dspace
