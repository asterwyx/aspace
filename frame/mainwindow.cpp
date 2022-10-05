#include "mainwindow.h"
#include <QList>
#include <QResizeEvent>
#include <DTitlebar>
#include <QDebug>
#include <QLabel>
#include <QtConcurrent>
BEGIN_USER_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
    , m_windowSettings(new QGSettings(SCHEMA_ID, SCHEMA_PATH, this))
    , m_dConfig(DConfig::create(DCONFIG_FILE, DCONFIG_FILE))
    , m_refreshButton(new HoverButton)
    , m_contentFrame(new QWidget(this))
    , m_contentLayout(new QVBoxLayout(m_contentFrame))
    , m_loadingPage(new LoadingPage(this))
{
    DTitlebar *titleBar = this->titlebar();
    titleBar->setIcon(QIcon::fromTheme("gnome-weather"));
    m_refreshButton->setIcon(QIcon::fromTheme("aspace_refresh"));
    m_refreshButton->setIconSize(30, 30);
    m_refreshButton->setBorderRadius(5);
    m_refreshButton->setBackgroundWidget(titleBar);
    titleBar->addWidget(m_refreshButton, Qt::AlignLeft);
    setWindowIcon(QIcon::fromTheme("gnome-weather"));
    m_contentFrame->move(0, titleBar->height());  // Move to the content area.
    m_contentFrame->setWindowFlag(Qt::FramelessWindowHint);
    m_contentFrame->setAttribute(Qt::WA_TranslucentBackground);
    m_loadingPage->move(0, titleBar->height());
    connect(m_refreshButton, &HoverButton::clicked, this, &MainWindow::refresh);
    setFixedSize(LIST_WIDGET_WIDTH * 3 + LISTVIEW_ITEM_SPACING * 3,
                 LIST_WIDGET_WIDTH + LIST_WIDGET_HEIGHT + titleBar->height() + LISTVIEW_ITEM_SPACING);
    m_contentFrame->resize(width(), height() - titleBar->height());
    m_loadingPage->resize(width(), height() - titleBar->height());
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Enter) {
        qDebug() << obj << event;
    } else if (event->type() == QEvent::Leave) {
        qDebug() << obj << event;
    }
    return DMainWindow::eventFilter(obj, event);
}

void MainWindow::initializeAllPlugins()
{
    foreach (PluginInterface *plugin, m_plugins) {
        plugin->initialize();
    }
}

void MainWindow::loadData()
{
    foreach (PluginInterface *plugin, m_plugins) {
        plugin->loadData();
    }
    showContents();
}

void MainWindow::showContents()
{
    m_loadingPage->hide();
    m_contentFrame->show();
}

QPointer<QGSettings> MainWindow::getWindowSettings()
{
    return {m_windowSettings};
}

QPointer<DConfig> MainWindow::getDConfig()
{
    return {m_dConfig};
}

MainWindow::~MainWindow() = default;

QSize MainWindow::getFrameSize()
{
    return this->m_contentFrame->size();
}

void MainWindow::pluginAdded(PluginInterface *plugin)
{
    m_plugins.append(plugin);
}

void MainWindow::addItem(PluginInterface *pluginToAdd, const QString &itemKey)
{
    if (itemKey.isEmpty()) {
        qWarning() << "Item key cannot be empty.";
        return;
    }
    if (!m_itemMap.contains(itemKey)) {
        QWidget *itemWidget = pluginToAdd->pluginItemWidget(itemKey);
        if (itemWidget) {
            m_contentLayout->addWidget(itemWidget, Qt::AlignCenter);
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

void MainWindow::removeItem(const QString &itemKey)
{
    m_itemMap.remove(itemKey);
}

void MainWindow::updateItem(const QString &itemKey)
{
    m_itemMap[itemKey]->update();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_contentFrame->resize(event->size().width(), event->size().height() - titlebar()->height());
    DMainWindow::resizeEvent(event);
}

QList<PluginInterface *> MainWindow::plugins()
{
    return m_plugins;
}

void MainWindow::refresh()
{
    qDebug() << "Refresh.";
    QtConcurrent::run([=] { this->loadData(); });
}

void MainWindow::showSplash()
{
    m_contentFrame->hide();
    m_loadingPage->show();
}

END_USER_NAMESPACE
