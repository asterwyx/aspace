#pragma once
#include "common_def.h"
#include "page.h"
#include "frameproxyinterface.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

BEGIN_USER_NAMESPACE

class ContentPage : public Page, public FrameProxyInterface
{
    Q_OBJECT
public:
    explicit ContentPage(MainWindow *parent = nullptr);

    void addItem(PluginInterface *pluginToAdd, const QString &itemKey) override;
    void removeItem(const QString &itemKey) override;
    void updateItem(const QString &itemKey) override;
    void initializeAllPlugins() override;
    void pluginAdded(PluginInterface *plugin) override;
    QList<PluginInterface *> plugins() override;
    QSize getFrameSize() override;
    void loadData();

private:
    QMap<QString, QWidget *> m_itemMap;
    QList<PluginInterface *> m_plugins;
    QVBoxLayout *m_layout;
};

END_USER_NAMESPACE
