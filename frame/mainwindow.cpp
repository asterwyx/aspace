#include "mainwindow.h"
#include <QList>
#include <QResizeEvent>
#include <DTitlebar>
#include <QDebug>
#include <QLabel>
#include <QtConcurrent>
#include <QStackedLayout>
#include "loadingpage.h"
#include "selectingpage.h"
#include "contentpage.h"
BEGIN_USER_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
    , m_windowSettings(new QGSettings(SCHEMA_ID, SCHEMA_PATH, this))
    , m_dConfig(DConfig::create(DCONFIG_FILE, DCONFIG_FILE))
    , m_refreshButton(new HoverButton)
    , m_contentFrame(new QWidget(this))
    , m_loadingPage(new LoadingPage(this))
    , m_selectingPage(new SelectingPage(this))
    , m_contentPage(new ContentPage(this))
    , m_stackedLayout(new QStackedLayout(m_contentFrame))
{
    DTitlebar *titleBar = this->titlebar();
    setFixedSize(LIST_WIDGET_WIDTH * 3 + LISTVIEW_ITEM_SPACING * 3,
                 LIST_WIDGET_WIDTH + LIST_WIDGET_HEIGHT + titleBar->height() + LISTVIEW_ITEM_SPACING);
    m_stackedLayout->addWidget(m_selectingPage);
    m_stackedLayout->addWidget(m_loadingPage);
    m_stackedLayout->addWidget(m_contentPage);
    m_stackedLayout->setCurrentWidget(m_selectingPage);
    m_contentFrame->resize(width(), height() - titleBar->height());
    m_contentFrame->move(0, titleBar->height());  // Move to the content area.
    m_contentFrame->setWindowFlag(Qt::FramelessWindowHint);
    m_contentFrame->setAttribute(Qt::WA_TranslucentBackground);
    titleBar->setIcon(QIcon::fromTheme("gnome-weather"));
    m_refreshButton->setIcon(QIcon::fromTheme("aspace_refresh"));
    m_refreshButton->setIconSize(30, 30);
    m_refreshButton->setBorderRadius(5);
    m_refreshButton->setBackgroundWidget(titleBar);
    titleBar->addWidget(m_refreshButton, Qt::AlignLeft);
    setWindowIcon(QIcon::fromTheme("gnome-weather"));
    connect(m_refreshButton, &HoverButton::clicked, this, &MainWindow::refresh);
    connect(m_selectingPage, &SelectingPage::citySelected, this, [=] { QTimer::singleShot(3, [=] { this->showContents(); }); });
}

void MainWindow::showContents()
{
    m_contentPage->loadData();
    m_stackedLayout->setCurrentWidget(m_contentPage);
}

QPointer<QGSettings> MainWindow::getWindowSettings()
{
    return m_windowSettings;
}

QPointer<DConfig> MainWindow::getDConfig()
{
    return m_dConfig;
}

QPointer<DConfig> MainWindow::writeDConfig()
{
    delete m_dConfig;
    m_dConfig = DConfig::create(DCONFIG_FILE, DCONFIG_FILE);
    return m_dConfig;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_contentFrame->resize(event->size().width(), event->size().height() - titlebar()->height());
    DMainWindow::resizeEvent(event);
}

void MainWindow::refresh()
{
    QtConcurrent::run([=] { m_contentPage->loadData(); });
}

void MainWindow::showSplash()
{
    m_stackedLayout->setCurrentWidget(m_loadingPage);
}

QPointer<ContentPage> MainWindow::getContentPage()
{
    return m_contentPage;
}

void MainWindow::showSelect()
{
    m_stackedLayout->setCurrentWidget(m_selectingPage);
}

END_USER_NAMESPACE
