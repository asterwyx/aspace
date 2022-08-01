#pragma once
#include <QList>
#include <plugininterface.h>
#include <qglobal.h>

namespace dspace {
class PluginLoaderPrivate;
class PluginLoader {
public:
    PluginLoader(const QString &pluginsDir);
    ~PluginLoader();
    QList<PluginInterface>  *loadPlugins();
    void                    showAllPlugins();

private:
    Q_DECLARE_PRIVATE(PluginLoader)
    PluginLoaderPrivate *d_ptr;
};
}