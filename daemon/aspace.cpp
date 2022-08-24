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
#include <QDateTime>
#include <QEventLoop>

BEGIN_USER_NAMESPACE
Aspace::Aspace(QObject *parent) : QObject(parent) {}

Aspace::~Aspace() = default;

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

bool Aspace::updateLocationId(const QString &name)
{
    bool result = false;
    setLocationName(name);
    QString urlString("https://geoapi.qweather.com/v2/city/lookup?key=");
    urlString += apiKey();
    urlString += "&location=";
    urlString += name;
    qInfo() << "Request url:" << urlString;
    QUrl url = QUrl::fromUserInput(urlString);
    assert(url.isValid());
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"); // grant that we get a json string
    QNetworkReply *reply = m_networkManager.get(request);
    QEventLoop loop;
    QTimer::singleShot(REQUEST_TIMEOUT, &loop, [&] {
        if (loop.isRunning())
            loop.quit();
    });
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(QEventLoop::ExcludeUserInputEvents);
    if (reply->isFinished())
    {
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
                    QJsonObject cityLocation;
                    if (citys.isArray())
                    {
                        QJsonArray cityArr = citys.toArray();
                        // TODO: Add result filter
                        cityLocation = cityArr[0].toObject();
                    }
                    else
                    {
                        cityLocation = citys.toObject();
                    }                
                    m_currentWeather.location.name = cityLocation.value("name").toString();
                    m_currentWeather.location.id = cityLocation.value("id").toString();
                    m_currentWeather.location.latitude = cityLocation.value("lat").toString().toDouble();
                    m_currentWeather.location.longitude = cityLocation.value("lon").toString().toDouble();
                    m_currentWeather.location.adm2 = cityLocation.value("adm2").toString();
                    m_currentWeather.location.adm1 = cityLocation.value("adm1").toString();
                    m_currentWeather.location.country = cityLocation.value("country").toString();
                    m_currentWeather.location.timezone = cityLocation.value("tz").toString();
                    m_currentWeather.location.utcOffset = cityLocation.value("utcOffset").toString();
                    m_currentWeather.location.isDst = cityLocation.value("isDst").toString().toInt();
                    emit locationIdUpdated(m_currentWeather.location.id);
                    result = true;
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
    }
    else
    {
        reply->abort();
        qWarning() << "Request" << urlString << "timeout.";
    }
    reply->close();
    reply->deleteLater();
    return result;
}

bool Aspace::updateWeather(QString locationId)
{
    bool result = false;
    if (locationId.isEmpty())
        locationId = m_currentWeather.location.id;
    qDebug() << "Updating weather, city code:" << locationId;
    QString urlStr("https://devapi.qweather.com/v7/weather/now?key=");
    urlStr += apiKey();
    urlStr += "&location=";
    urlStr += locationId;
    qInfo() << "Request url:" << urlStr;
    QUrl url = QUrl::fromUserInput(urlStr);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_networkManager.get(request);
    // Use local event loop to wait
    QEventLoop loop;
    QTimer::singleShot(REQUEST_TIMEOUT, &loop, [&]{
        if (loop.isRunning())
            loop.quit();
    }); // Setting wait timeout
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(QEventLoop::ExcludeUserInputEvents); // Just wait for non user input events

    if (reply->isFinished())
    {
        // Check normally finished or timeout
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
                    // extract weather info
                    QJsonObject currentWeather = rootObj.value("now").toObject();
                    m_currentWeather.observedTime = QDateTime::fromString(currentWeather.value("obsTime").toString(), Qt::ISODate);
                    m_currentWeather.temperature = currentWeather.value("temp").toString().toDouble();
                    m_currentWeather.feelsLikeTemperature = currentWeather.value("feelsLike").toString().toDouble();
                    m_currentWeather.iconName = currentWeather.value("icon").toString();
                    m_currentWeather.description = currentWeather.value("text").toString();
                    m_currentWeather.wind360 = currentWeather.value("wind360").toString().toDouble();
                    m_currentWeather.windDirection = currentWeather.value("windDir").toString().toDouble();
                    m_currentWeather.windScale = currentWeather.value("windScale").toString().toDouble();
                    m_currentWeather.windSpeed = currentWeather.value("windSpeed").toString().toDouble();
                    m_currentWeather.humidity = currentWeather.value("humidity").toString().toDouble();
                    m_currentWeather.precip = currentWeather.value("precip").toString().toDouble();
                    m_currentWeather.pressure = currentWeather.value("pressure").toString().toDouble();
                    m_currentWeather.visibility = currentWeather.value("vis").toString().toDouble();
                    m_currentWeather.cloud = currentWeather.value("cloud").isNull() ? 0.0 : currentWeather.value("cloud").toString().toDouble();
                    m_currentWeather.dew = currentWeather.value("dew").isNull() ? 0.0 : currentWeather.value("dew").toString().toDouble();
                    emit weatherUpdated(m_currentWeather);
                    result = true;
                }
            }
            else
            {
                qWarning() << "Parse json error:" << parseErr.error << parseErr.errorString();
            }
        }
        else
        {
            qWarning() << "Request" << urlStr << "error:" << reply->error() << reply->errorString();
        }
    }
    else
    {
        reply->abort();
        qWarning() << "Request" << urlStr << "timeout.";
    }
    reply->close();
    reply->deleteLater();
    return result;
}

void Aspace::setLocationName(QString location)
{
    m_currentWeather.location.name = location;
}

CurrentWeather Aspace::getCurrentWeather()
{
    if (updateLocationId(m_currentWeather.location.name) && updateWeather())
        return m_currentWeather;
    else
    {
        sendErrorReply(QDBusError::Failed, "Location or weather update failed!");
        return {};
    }
}

// QList<WeatherData> Aspace::getFutureWeather()
// {
//     // TODO implement the data acquiring.
//     return {
//         {WeatherOverview::SUNNY, TemperatureUnit::CELSIUS, 36, 30, 38, QString::fromUtf8("武汉")},
//         {WeatherOverview::SUNNY, TemperatureUnit::CELSIUS, 34, 28, 38, QString::fromUtf8("北京")}
//         };
// }

void Aspace::setTemperatureUnit(TemperatureUnit unit)
{
    m_currentWeather.changeTemperatureUnit(unit);
}
END_USER_NAMESPACE
