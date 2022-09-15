// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "aspace.h"
#include <QDebug>
#include <QDBusError>
#include <QCoreApplication>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
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

QList<Location> Aspace::lookForLocations(const QString &cityName, bool *ok)
{
    QList<Location> result;
    bool queried = false;
    QString urlString("https://geoapi.qweather.com/v2/city/lookup?key=");
    urlString += apiKey();
    urlString += "&location=";
    urlString += cityName;
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
            QJsonParseError parseErr{};
            QJsonDocument rootDoc = QJsonDocument::fromJson(rawBody, &parseErr);
            if (parseErr.error == QJsonParseError::NoError) {
                // extract api status code and city code
                QJsonObject rootObj = rootDoc.object();
                int apiCode = rootObj.value("code").toString().toInt();
                qDebug() << "Api code:" << apiCode;
                bool continued = parseApiCode(apiCode);
                if (continued)
                {
                    QJsonArray cityArr = rootObj.value("location").toArray();
                    foreach(QJsonValue city, cityArr)
                    {
                        QJsonObject cityLocation = city.toObject();
                        Location location;
                        location.name = cityLocation.value("name").toString();
                        location.id = cityLocation.value("id").toString();
                        location.latitude = cityLocation.value("lat").toString().toDouble();
                        location.longitude = cityLocation.value("lon").toString().toDouble();
                        location.adm2 = cityLocation.value("adm2").toString();
                        location.adm1 = cityLocation.value("adm1").toString();
                        location.country = cityLocation.value("country").toString();
                        location.timezone = cityLocation.value("tz").toString();
                        location.utcOffset = cityLocation.value("utcOffset").toString();
                        location.isDst = cityLocation.value("isDst").toString().toInt();
                        location.type = cityLocation.value("type").toString();
                        location.rank = cityLocation.value("rank").toString().toInt();
                        result.append(location);
                    }
                    queried = true; 
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
    if (ok)
    {
        *ok = queried;
    }
    if (queried)
    {
        return result;
    }
    else
    {
        sendErrorReply(QDBusError::Failed, "Failed to look for locations!");
        return {};
    }
}

CurrentWeather Aspace::getCurrentWeather(const QString &cityCode, bool *ok)
{
    CurrentWeather result;
    bool updated = false;
    if (cityCode.isEmpty())
    {
        sendErrorReply(QDBusError::InvalidArgs, "City code cannot be empty!");
        return {};
    }
    qDebug() << "Getting weather, city code:" << cityCode;
    QString urlStr("https://devapi.qweather.com/v7/weather/now?key=");
    urlStr += apiKey();
    urlStr += "&location=";
    urlStr += cityCode;
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
    loop.exec(QEventLoop::ExcludeUserInputEvents); // Just wait for non-user input events
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
            QJsonParseError parseErr{};
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
                    result.observedTime = QDateTime::fromString(currentWeather.value("obsTime").toString(), Qt::ISODate);
                    result.temperature = currentWeather.value("temp").toString().toDouble();
                    result.feelsLikeTemperature = currentWeather.value("feelsLike").toString().toDouble();
                    result.iconName = currentWeather.value("icon").toString();
                    result.description = currentWeather.value("text").toString();
                    result.wind360 = currentWeather.value("wind360").toString().toDouble();
                    result.windDirection = currentWeather.value("windDir").toString();
                    result.windScale = currentWeather.value("windScale").toString();
                    result.windSpeed = currentWeather.value("windSpeed").toString().toDouble();
                    result.humidity = currentWeather.value("humidity").toString().toDouble();
                    result.precip = currentWeather.value("precip").toString().toDouble();
                    result.pressure = currentWeather.value("pressure").toString().toDouble();
                    result.visibility = currentWeather.value("vis").toString().toDouble();
                    result.cloud = currentWeather.value("cloud").isNull() ? 0.0 : currentWeather.value("cloud").toString().toDouble();
                    result.dew = currentWeather.value("dew").isNull() ? 0.0 : currentWeather.value("dew").toString().toDouble();
                    updated = true;
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
    if(ok)
    {
        *ok = updated;
    }
    if(updated)
    {
        return result;
    }
    else
    {
        sendErrorReply(QDBusError::Failed, "Location or weather update failed!");
        return {};
    }
}

QList<FutureWeather> Aspace::getFutureWeather(const QString &cityCode, bool *ok) {
    QList<FutureWeather> result;
    bool updated = false;
    if (cityCode.isEmpty())
    {
        sendErrorReply(QDBusError::InvalidArgs, "City code cannot be empty!");
        return {};
    }
    qDebug() << "Getting future weather, city code:" << cityCode;
    QString urlStr("https://devapi.qweather.com/v7/weather/3d?key=");
    urlStr += apiKey();
    urlStr += "&location=";
    urlStr += cityCode;
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
    loop.exec(QEventLoop::ExcludeUserInputEvents); // Just wait for non-user input events
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
            QJsonParseError parseErr{};
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
                    QJsonArray dailyWeathers = rootObj.value("daily").toArray();
                    foreach(QJsonValue dailyWeather, dailyWeathers)
                    {
                        QJsonObject weatherObj = dailyWeather.toObject();
                        FutureWeather futureWeather;
                        futureWeather.forecastDate = QDate::fromString(weatherObj.value("fxDate").toString(), Qt::ISODate);
                        futureWeather.sunriseTime = QTime::fromString(weatherObj.value("sunrise").toString(), Qt::ISODate);
                        futureWeather.sunsetTime = QTime::fromString(weatherObj.value("sunset").toString(), Qt::ISODate);
                        futureWeather.moonriseTime = QTime::fromString(weatherObj.value("moonrise").toString(), Qt::ISODate);
                        futureWeather.moonsetTime = QTime::fromString(weatherObj.value("moonset").toString(), Qt::ISODate);
                        futureWeather.moonPhase = weatherObj.value("moonPhase").toString();
                        futureWeather.maxTemperature = weatherObj.value("tempMax").toString().toDouble();
                        futureWeather.minTemperature = weatherObj.value("tempMin").toString().toDouble();
                        futureWeather.iconDay = weatherObj.value("iconDay").toString();
                        futureWeather.textDay = weatherObj.value("textDay").toString();
                        futureWeather.iconNight = weatherObj.value("iconNight").toString();
                        futureWeather.textNight = weatherObj.value("textNight").toString();
                        futureWeather.wind360Day = weatherObj.value("wind360Day").toString().toDouble();
                        futureWeather.windDirectionDay = weatherObj.value("windDirDay").toString();
                        futureWeather.windScaleDay = weatherObj.value("windScaleDay").toString();
                        futureWeather.windSpeedDay = weatherObj.value("windSpeedDay").toString().toDouble();
                        futureWeather.wind360Night = weatherObj.value("wind360Night").toString().toDouble();
                        futureWeather.windDirectionNight = weatherObj.value("windDirNight").toString();
                        futureWeather.windScaleNight = weatherObj.value("windScaleNight").toString();
                        futureWeather.windSpeedNight = weatherObj.value("windSpeedNight").toString().toDouble();
                        futureWeather.humidity = weatherObj.value("humidity").toString().toDouble();
                        futureWeather.precip = weatherObj.value("precip").toString().toDouble();
                        futureWeather.pressure = weatherObj.value("pressure").toString().toDouble();
                        futureWeather.visibility = weatherObj.value("vis").toString().toDouble();
                        futureWeather.cloud = weatherObj.value("cloud").toString().toDouble();
                        futureWeather.uvIndex = weatherObj.value("uvIndex").toString().toDouble();
                        result.append(futureWeather);
                    }
                    updated = true;
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
    if(ok)
    {
        *ok = updated;
    }
    if(updated)
    {
        return result;
    }
    else
    {
        sendErrorReply(QDBusError::Failed, "Location or weather update failed!");
        return {};
    }
}
END_USER_NAMESPACE
