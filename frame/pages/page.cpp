#include "page.h"
#include "mainwindow.h"



Page::Page(MainWindow *parent)
    : QWidget(parent)
    , m_window(parent)
{
}

QPointer<DConfig> Page::dConfig()
{
    return m_window->getDConfig();
}

QPointer<QGSettings> Page::gSettings()
{
    return m_window->getWindowSettings();
}

QPointer<DConfig> Page::writeDConfig()
{
    return m_window->writeDConfig();
}
