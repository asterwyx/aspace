#include "page.h"

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
END_USER_NAMESPACE