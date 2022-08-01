#pragma once
#include <QList>
#include <plugininterface.h>
#include <qglobal.h>
#include <QScopedPointer>

namespace dspace {
class PluginLoaderPrivate;
class PluginLoader {
public:
    PluginLoader(const QString &pluginDir);
    PluginLoader(const QString &pluginDir, PluginLoaderPrivate &d);
    ~PluginLoader();
    bool                    loadPlugins();
    void                    showAllPlugins();

private:
    Q_DECLARE_PRIVATE(PluginLoader)
    QScopedPointer<PluginLoaderPrivate> d_ptr;
};
}