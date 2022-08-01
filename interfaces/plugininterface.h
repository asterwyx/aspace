#pragma once
#include <QtCore>

class PluginInterface
{

};

#define PLUGIN_INTERFACE_ID     "com.deepin.dde.space.plugin"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(PluginInterface, PLUGIN_INTERFACE_ID)
QT_END_NAMESPACE