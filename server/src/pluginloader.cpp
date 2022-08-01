#include "plugininterface.h"
#include <pluginloader.h>
#include <pluginloader_p.h>
#include <qglobal.h>
#include <qlist.h>

namespace dspace {
PluginLoader::PluginLoader(const QString &pluginDir)
    : d_ptr(new PluginLoaderPrivate(this))
{
    Q_D(PluginLoader);
    d->m_pluginDir = pluginDir;
}

PluginLoader::PluginLoader(const QString &pluginDir, PluginLoaderPrivate &dd)
    : d_ptr(&dd)
{
    Q_D(PluginLoader);
    d->m_pluginDir = pluginDir;
}

PluginLoader::~PluginLoader()
{
    Q_D(PluginLoader);
    for (PluginInterface *plugin : d->m_plugins)
    {
        delete plugin;
    }
}


bool PluginLoader::loadPlugins()
{
    Q_D(PluginLoader);
    return d->loadPlugins();
}

void PluginLoader::showAllPlugins()
{

}
}
