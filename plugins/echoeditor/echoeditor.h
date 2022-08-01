#pragma once
#include <QWidget>
#include <QString>
#include <plugininterface.h>
namespace dspace {
class EchoEditor: public QWidget, public PluginInterface {
public:
    EchoEditor();
    ~EchoEditor();
    const QString pluginName() const;
    const QString pluginDisplayName() const;
    

};
}