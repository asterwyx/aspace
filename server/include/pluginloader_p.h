#pragma once
#include "pluginloader.h"
#include <QString>
#include <qlist.h>
namespace dspace {
class PluginLoaderPrivate {
public:
    PluginLoaderPrivate(PluginLoader *q);
    ~PluginLoaderPrivate();

protected:
    bool loadPlugins();
    

private:
    Q_DECLARE_PUBLIC(PluginLoader)
    PluginLoader                    *q_ptr;
    QString                         m_pluginDir;
    QList<PluginInterface *>        m_plugins;
};


}