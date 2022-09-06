#include "mainwindow.h"
#include <QMap>
#include <QList>
#include <QVariant>
#include <QDebug>
#include <QResizeEvent>

BEGIN_USER_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_windowSettings(new QGSettings(SCHEMA_ID, SCHEMA_PATH, this)),
    m_saveLastWindowSize(false)
{
    this->setMinimumSize(200, 200);
}

void MainWindow::initializeAllPlugins()
{
    foreach(PluginInterface *plugin, m_plugins)
    {
        plugin->initialize();
    }
}

MainWindow::~MainWindow()
{
    // Save window size if save last window size option is on
    if (m_saveLastWindowSize)
        this->setSize(this->size());
}

QSize MainWindow::getFrameSize()
{
    return this->size();
}

void MainWindow::loadDefaultSize() {
    bool wOk = false, hOk = false;
    int width = m_windowSettings->get("window-width").toInt(&wOk);
    if (!wOk)
    {
        qWarning() << "Cannot convert window width gsetting value to int.";
        return;
    }
    int height = m_windowSettings->get("window-height").toInt(&hOk);
    if (!hOk)
    {
        qWarning() << "Cannot convert window height gsetting value to int.";
        return;
    }
    this->resize(width, height);
}
void MainWindow::addPlugin(PluginInterface *plugin)
{
    FrameProxyInterface::addPlugin(plugin);
    m_plugins.push_back(plugin);
}

bool MainWindow::isSaveLastWindowSize() {
    return m_saveLastWindowSize;
}

void MainWindow::setSaveLastWindowSize(bool enable) {
    m_saveLastWindowSize = enable;
}

void MainWindow::setSize(const QSize &size) {
    bool set = m_windowSettings->trySet("window-width", size.width());
    if (set)
    {
        set = m_windowSettings->trySet("window-height", size.height());
        if (!set)
        {
            qWarning() << "Window height set failed, but width is still set!";
        }
    }
    else
    {
        qWarning() << "Window width set failed!";
    }
}

void MainWindow::addItem(PluginInterface *pluginToAdd, const QString &itemKey) {
    if (!m_itemMap.contains(itemKey))
    {
        QWidget *itemWidget = pluginToAdd->pluginItemWidget(itemKey);
        itemWidget->setParent(this);
        m_itemMap.insert(itemKey, itemWidget);
    }
    else
    {
        if (!m_plugins.contains(pluginToAdd))
        {
            qWarning() << "Please specify a unique item ket among all plugin items.";
        }
        else
        {
            qWarning() << "Item" << itemKey << "is already added.";
        }
    }
}

void MainWindow::removeItem(const QString &itemKey) {
    m_itemMap.remove(itemKey);
}

void MainWindow::updateItem(const QString &itemKey) {
    m_itemMap[itemKey]->update();
}

void MainWindow::resizeEvent(QResizeEvent *event) {

    QWidget::resizeEvent(event);
}


END_USER_NAMESPACE