#include "pluginloader.h"
#include <pluginloader_p.h>

namespace dspace {
PluginLoaderPrivate::PluginLoaderPrivate(PluginLoader *q) : q_ptr(q) {}
PluginLoaderPrivate::~PluginLoaderPrivate() { }

bool PluginLoaderPrivate::loadPlugins()
{
    return true;
}
}