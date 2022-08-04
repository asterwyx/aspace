#pragma once
#include "plugininterface.h"
#include <QList>
#include <QScopedPointer>
#include <QtGlobal>

namespace dspace {
class PluginLoaderPrivate;
class PluginLoader {
public:
    PluginLoader();
    explicit PluginLoader(const QString &pluginDir);
    PluginLoader(const QString &pluginDir, PluginLoaderPrivate &d);
    ~PluginLoader();
    bool                            loadPlugins();
    void                            showAllPlugins(QWidget *parent);
    void                            addPluginDir(QString pluginDir);
    const QList<PluginInterface *>  *getPlugins();

private:
    Q_DECLARE_PRIVATE(PluginLoader)
    QScopedPointer<PluginLoaderPrivate> d_ptr;
};
} // namespace dspace