#include "selectingpage.h"
#include <QLineEdit>
#include "weatherinterface.h"

BEGIN_USER_NAMESPACE
SelectingPage::SelectingPage(MainWindow *parent)
    : Page(parent)
    , m_lineEditLayout(new QHBoxLayout(this))
    , m_welcomeLabel(new QLabel(tr("欢迎使用aspace, 请设置您的城市: "), this))
    , m_hintLabel(new QLabel(tr("城市: "), this))
    , m_resultLabel(new QLabel(this))
    , m_cityLineEdit(new QLineEdit(this))
    , m_confirmButton(new QPushButton(tr("查询"), this))
{
    m_hintLabel->setAlignment(Qt::AlignRight);
    m_lineEditLayout->addWidget(m_hintLabel, 1);
    m_lineEditLayout->addWidget(m_cityLineEdit, 2);
    connect(m_confirmButton, &QPushButton::clicked, this, &SelectingPage::onConfirmed);
}

void SelectingPage::onConfirmed()
{
    if (!m_cityLineEdit->text().isEmpty()) {
        WeatherInterface inter(DBUS_SERVICE_NAME, DBUS_ASPACE_PATH, QDBusConnection::sessionBus());
        QList<Location> locations = inter.lookForLocations(m_cityLineEdit->text());
        if (locations.isEmpty()) {
            m_resultLabel->setText("无法查询到相关的城市, 请检查输入后重试");
        } else {
            auto config = dConfig();
            if (config) {
                config->setValue("locationId", locations[0].id);
                config->setValue("locationName", locations[0].name);
                emit this->citySelected(locations[0].id);
            } else {
                qCritical() << "Invalid DConfig pointer from mainwindow!";
            }
        }
    } else {
        m_resultLabel->setText("请输入有效的字符串");
    }
}
END_USER_NAMESPACE