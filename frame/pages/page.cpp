#include "page.h"
#include "mainwindow.h"

BEGIN_USER_NAMESPACE

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
END_USER_NAMESPACE