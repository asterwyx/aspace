#pragma once
#include "plugininterface.h"
#include <QScopedPointer>
#include <QString>
#include <QWidget>
#include <QtGlobal>
namespace dspace {
class EchoEditorPrivate;
class EchoEditor : public QWidget, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_INTERFACE_ID)
    Q_INTERFACES(PluginInterface)

public:
  EchoEditor(QWidget *parent = nullptr);
  ~EchoEditor();
  const QString pluginName() const;
  const QString pluginDisplayName() const;
  QWidget *pluginWidget(const QString &key);

private:
  Q_DECLARE_PRIVATE(EchoEditor)
  QScopedPointer<EchoEditorPrivate> d_ptr;
};
} // namespace dspace
