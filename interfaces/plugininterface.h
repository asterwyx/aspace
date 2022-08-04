#pragma once
#include <QWidget>
class PluginInterface {
public:

  /**
   * @brief Destroy the Plugin Interface object
   *
   */
  virtual ~PluginInterface() {}

  /**
   * @brief Return the only name of a plugin, this is a must-need name
   *
   * @return const QString
   */
  virtual QString pluginName() const = 0;

  /**
   * @brief Overwrite this function if you want a different display name
   *
   * @return const QString
   */
  virtual QString pluginDisplayName() const { return QString(""); }

  /**
   * @brief Get the widget of the plugin
   *
   * @param key the only identifier for the plugin
   * @return QWidget* the widget
   */
  virtual QWidget *pluginWidget(const QString &key) = 0;
};

#define PLUGIN_INTERFACE_ID "org.deepin.dde.space.plugin"
QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(PluginInterface, PLUGIN_INTERFACE_ID)
QT_END_NAMESPACE