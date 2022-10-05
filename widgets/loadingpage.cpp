#include "loadingpage.h"

BEGIN_USER_NAMESPACE
LoadingPage::LoadingPage(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout(this))
    , m_loadingLabel(new QLabel("Loading...", this))
{
    m_loadingLabel->setAlignment(Qt::AlignCenter);
    m_layout->addWidget(m_loadingLabel);
    setLayout(m_layout);
}

END_USER_NAMESPACE