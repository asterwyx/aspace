#pragma once
#include "common_def.h"
#include "plugininterface.h"
#include <QWidget>


BEGIN_USER_NAMESPACE
class FrameProxyInterface {
public:
    // 一个插件可以有多个item，这主要是为了解决同一个插件的item布局不一致的问题，此时可以使用两个插件，itemKey在itemWidget调用的时候使用
    virtual void itemAdded(PluginInterface *pluginToAdd, const QString &itemKey) = 0;
    // Remove spec item
    virtual void itemRemoved(const QString &itemKey) = 0;
    // Update spec item
    virtual void itemUpdated(const QString &itemKey) = 0;

    virtual QSize getSize() = 0;
};
END_USER_NAMESPACE