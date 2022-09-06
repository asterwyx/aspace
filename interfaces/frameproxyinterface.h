#pragma once
#include "common_def.h"
#include "plugininterface.h"
#include <QWidget>


BEGIN_USER_NAMESPACE
class FrameProxyInterface {
public:
    // A plugin can add multiple items, this is for scattered position of items belonging to a plugin
    virtual void addItem(PluginInterface *pluginToAdd, const QString &itemKey) = 0;
    // Remove spec item
    virtual void removeItem(const QString &itemKey) = 0;
    // Update spec item
    virtual void updateItem(const QString &itemKey) = 0;
    // Initialize all plugins which is implicitly added by addItem function
    virtual void initializeAllPlugins() = 0;
    // Add a plugin
    virtual void addPlugin(PluginInterface *plugin)
    {
        plugin->setFrameProxy(this);
        plugin->preInitialize();
    }
    // Get the current size of the frame proxy, for plugin layout convenience
    virtual QSize getFrameSize() = 0;
};
END_USER_NAMESPACE