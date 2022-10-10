#include "contentpage.h"
#include <QDebug>
#include <QVBoxLayout>
BEGIN_USER_NAMESPACE
ContentPage::ContentPage(MainWindow *parent)
    : Page(parent)
    , m_layout(new QVBoxLayout(this))
{
}

void ContentPage::addItem(PluginInterface *pluginToAdd, const QString &itemKey)
{
    if (itemKey.isEmpty()) {
        qWarning() << "Item key cannot be empty.";
        return;
    }
    if (!m_itemMap.contains(itemKey)) {
        QWidget *itemWidget = pluginToAdd->pluginItemWidget(itemKey);
        if (itemWidget) {
            m_layout->addWidget(itemWidget, Qt::AlignCenter);
            m_itemMap.insert(itemKey, itemWidget);
        } else {
            qWarning() << "Item key" << itemKey << "cannot get a item widget from plugin" << pluginToAdd;
        }
    } else {
        if (!m_plugins.contains(pluginToAdd)) {
            qWarning() << "Please specify a unique item ket among all plugin items.";
        } else {
            qWarning() << "Item" << itemKey << "is already added.";
        }
    }
}

void ContentPage::removeItem(const QString &itemKey)
{
    m_itemMap.remove(itemKey);
}

void ContentPage::updateItem(const QString &itemKey)
{
    m_itemMap[itemKey]->update();
}

void ContentPage::initializeAllPlugins()
{
    foreach (PluginInterface *plugin, m_plugins) {
        plugin->initialize();
    }
}

void ContentPage::pluginAdded(PluginInterface *plugin)
{
    m_plugins.append(plugin);
}

QList<PluginInterface *> ContentPage::plugins()
{
    return m_plugins;
}

QSize ContentPage::getFrameSize()
{
    return size();
}

void ContentPage::loadData()
{
    foreach (PluginInterface *plugin, m_plugins) {
        plugin->loadData();
    }
}

END_USER_NAMESPACE
