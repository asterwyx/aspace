#include "mainwindow.h"
#include <QMap>
#include <QList>
#include <QVariant>
#include <QDebug>

BEGIN_USER_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_windowSettings(new QGSettings(SCHEMA_ID, SCHEMA_PATH, this)),
    m_saveLastWindowSize(false)
{
}

MainWindow::~MainWindow()
{
    // Save window size if save last window size option is on
    if (m_saveLastWindowSize)
        this->setSize(this->size());
}

QSize MainWindow::getSize()
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

void MainWindow::itemAdded(PluginInterface *pluginToAdd, const QString &itemKey) {
    if (!m_plugins.contains(pluginToAdd)) {
        m_plugins.append(pluginToAdd);
    }
    m_itemMap.insert(itemKey, {pluginToAdd, pluginToAdd->pluginItemWidget(itemKey)});
}

void MainWindow::itemRemoved(const QString &itemKey) {
    m_itemMap.remove(itemKey);
}

void MainWindow::itemUpdated(const QString &itemKey) {
    m_itemMap[itemKey].second->update();
}


END_USER_NAMESPACE