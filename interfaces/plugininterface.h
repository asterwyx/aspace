#pragma once
#include <QtCore>

class PluginInterface
{
public:
    /**
     * @brief Destroy the Plugin Interface object
     * 
     */

    PluginInterface() = default;

    virtual ~PluginInterface() {}


    /**
     * @brief Return the only name of a plugin, this is a must-need name
     * 
     * @return const QString 
     */
    virtual const QString pluginName() const = 0;

    /**
     * @brief Overwrite this function if you want a different display name
     * 
     * @return const QString 
     */
    virtual const QString pluginDisplayName() const {return QString();}

    /**
     * @brief Get the widget of the plugin
     * 
     * @param itemKey the only identifier for the plugin
     * @return QWidget* the widget
     */
    virtual QWidget *itemWidget(const QString &itemKey) = 0;
};

#define PLUGIN_INTERFACE_ID     "com.deepin.dde.space.plugin"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(PluginInterface, PLUGIN_INTERFACE_ID)
QT_END_NAMESPACE