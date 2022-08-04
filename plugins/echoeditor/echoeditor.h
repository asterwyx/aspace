#pragma once
#include "plugininterface.h"
#include <QScopedPointer>
#include <QString>
#include <QWidget>
#include <QtGlobal>
namespace dspace {
class EchoEditorPrivate;
class EchoEditor : public QObject, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_INTERFACE_ID)
    Q_INTERFACES(PluginInterface)

public:
    EchoEditor();
    ~EchoEditor() override;
    QString pluginName() const override;
    QString pluginDisplayName() const override;
    QWidget *pluginWidget(const QString &key) override;

private:
    Q_DECLARE_PRIVATE(EchoEditor)
    QScopedPointer<EchoEditorPrivate> d_ptr;
};
} // namespace dspace
