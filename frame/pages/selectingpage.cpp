#include "selectingpage.h"
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include "weatherinterface.h"
#include <QApplication>

#include "mainwindow.h"

BEGIN_USER_NAMESPACE
SelectingPage::SelectingPage(MainWindow *parent)
    : Page(parent)
    , m_inputBox(new QGroupBox(this))
    , m_contentLayout(new QVBoxLayout(this))
    , m_welcomeLabel(new QLabel(tr("欢迎使用aspace\n请设置您的城市"), this))
    , m_hintLabel(new QLabel(tr("城市: "), m_inputBox))
    , m_cityLineEdit(new QLineEdit(m_inputBox))
    , m_confirmButton(new QPushButton(tr("查询"), m_inputBox))
    , m_resultLabel(new QLabel(this))
{
    m_contentLayout->setAlignment(Qt::AlignHCenter);
    m_inputBox->setFixedSize(400, 120);
    m_hintLabel->move(15, 15);
    m_hintLabel->resize(50, 40);
    m_hintLabel->setAlignment(Qt::AlignCenter);
    m_cityLineEdit->resize(300, 40);
    m_cityLineEdit->move(70, 15);
    m_confirmButton->resize(300, 40);
    m_confirmButton->move(50, 65);
    // m_hintLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    auto font = m_welcomeLabel->font();
    font.setPointSize(32);
    font.setWeight(100);
    m_welcomeLabel->setFont(font);
    m_welcomeLabel->setAlignment(Qt::AlignCenter);

    m_resultLabel->setAlignment(Qt::AlignCenter);
    connect(m_confirmButton, &QPushButton::clicked, this, &SelectingPage::onConfirmed);

    m_contentLayout->addWidget(m_welcomeLabel);
    m_contentLayout->addWidget(m_inputBox);
    m_contentLayout->addWidget(m_resultLabel);
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
            auto settings = gSettings();
            if (config) {
                config->setValue("locationId", locations[0].id);
                config->setValue("locationName", locations[0].name);
                settings->set("first-run", false);
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