// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <QObject>
#include <QList>
#include <QDBusArgument>
#include <QDBusConnection>
#include <QTimer>
#include <QDBusContext>
#include <QNetworkAccessManager>

#include "common_def.h"
#include "weatherdata.h"

BEGIN_USER_NAMESPACE

class Aspace : public QObject, public QDBusContext
{
    Q_OBJECT
public:
    explicit Aspace(QObject *parent = nullptr);
    ~Aspace() override;
    static constexpr uint REQUEST_TIMEOUT = 5000;  // ms
    static bool parseApiCode(int apiCode);
    inline static const char *apiKey() { return "b3aeb3cb72a74857b66a1f423c15bb89"; }

public slots:
    USER_NAMESPACE::CurrentWeather getCurrentWeather(const QString &cityCode, bool *ok = nullptr);
    QList<USER_NAMESPACE::Location> lookForLocations(const QString &cityName, bool *ok = nullptr);
    QList<USER_NAMESPACE::FutureWeather> getFutureWeather(const QString &cityCode, bool *ok = nullptr);

private:
    QNetworkAccessManager m_networkManager;
};

END_USER_NAMESPACE
