// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "aspace.h"
#include <QDBusConnection>
#include <QDBusMetaType>
#include <QDebug>
#include <QDBusError>
#include <QCoreApplication>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QSharedPointer>
#include <QJsonArray>

BEGIN_USER_NAMESPACE
Aspace::Aspace(QObject *parent) : QObject(parent), m_networkManager(new QNetworkAccessManager){}

Aspace::~Aspace()
{
    m_networkManager->dumpObjectTree();
    delete m_networkManager;
}

bool Aspace::parseApiCode(int apiCode)
{
    switch (apiCode)
    {
    case 200:
        // successful and valid data
        qInfo() << "Successful request and get some data.";
        return true;
    case 204:
        qWarning() << "Successful request but no match data.";
        return false;
    case 400:
        qWarning() << "Request error, possibly lack params or wrong params.";
        return false;
    case 401:
        qWarning() << "Authenticate error, possibly using wrong key or wrong signature or wrong key type.";
        return false;
    case 402:
        qWarning() << "Exceed request limits.";
    // TODO: Add more code parse
    default:
        qWarning() << "Unknown api code.";
        return false;
    }
}

static void doDelete(QObject *obj)
{
    // emit obj->destroyed(obj);
    qDebug() << "destroying" << obj;
    delete obj;
}

bool Aspace::getCityCode(const QString &name)
{
    setLocation(name);
    QString urlString("https://geoapi.qweather.com/v2/city/lookup?key=");
    urlString += apiKey();
    urlString += "&location=";
    urlString += name;
    qInfo() << "Request url:" << urlString;
    QUrl url = QUrl::fromUserInput(urlString);
    assert(url.isValid());
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"); // grant that we get a json string
    m_networkManager->dumpObjectTree();
    QSharedPointer<QNetworkReply> reply(m_networkManager->get(request), doDelete);
    m_networkManager->dumpObjectTree();
    connect(reply.data(), &QNetworkReply::finished, this, [this, reply, urlString] () mutable {
        // judge status code
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qInfo() << "Reply status code:" << statusCode;
        if (reply->error() == QNetworkReply::NoError)
        {
            // successful, get raw data and log(debug), convert to json document
            QByteArray rawBody = reply->readAll();
            QString bodyStr = QString::fromLocal8Bit(rawBody);
            qDebug() << "Reply body:" << bodyStr;
            QJsonParseError parseErr;
            QJsonDocument rootDoc = QJsonDocument::fromJson(rawBody, &parseErr);
            if (parseErr.error == QJsonParseError::NoError) {
                // extract api status code and city code
                QJsonObject rootObj = rootDoc.object();
                int apiCode = rootObj.value("code").toString().toInt();
                qDebug() << "Api code:" << apiCode;
                bool continued = parseApiCode(apiCode);
                if (continued)
                {
                    QJsonValue citys = rootObj.value("location");
                    if (citys.isArray())
                    {
                        QJsonArray cityArr = citys.toArray();
                        // TODO: Add result filter
                        m_cityCode = cityArr[0].toObject().value("id").toString();
                    }
                    else
                    {
                        m_cityCode = citys.toObject().value("id").toString();
                    }
                    emit cityCodeUpdated(m_cityCode);
                }
            }
            else
            {
                qWarning() << "Parse json error:" << parseErr.error << parseErr.errorString();
            }
        }
        else
        {
            qWarning() << "Request" << urlString << "error:" << reply->error() << reply->errorString();
        }
        m_networkManager->dumpObjectTree();
        // reply.clear();
        m_networkManager->dumpObjectTree();
    });
    connect(reply.data(), &QObject::destroyed, this, []{
        qDebug() << "Networkreply destroyed.";
    });
    // if get a pending reply, true
    return reply;
}

void Aspace::updateWeather(QString cityCode)
{
    if (cityCode.isEmpty())
        cityCode = m_cityCode;
    qDebug() << "Updating weather, city code:" << cityCode;
    // TODO: Update weather
}

void Aspace::setLocation(QString location)
{
    m_currentWeather.location = location;
}

WeatherData Aspace::getCurrentWeather()
{    
    bool constructed = getCityCode(m_currentWeather.location);
    if (!constructed)
    {
        qWarning() << "Request for city code error.";
    }
    else
    {
        connect(this, &Aspace::cityCodeUpdated, this, &Aspace::updateWeather);
    }
    return m_currentWeather;
}

QList<WeatherData> Aspace::getFutureWeather()
{
    // TODO implement the data acquiring.
    return {
        {WeatherOverview::SUNNY, TemperatureUnit::CELSIUS, 36, 30, 38, QString::fromUtf8("武汉")},
        {WeatherOverview::SUNNY, TemperatureUnit::CELSIUS, 34, 28, 38, QString::fromUtf8("北京")}
        };
}

void Aspace::setTemperatureUnit(TemperatureUnit unit)
{
    m_currentWeather.changeTemperatureUnit(unit);
}
END_USER_NAMESPACE
