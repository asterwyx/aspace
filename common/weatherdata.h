// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>
#include <QList>
#include <QDBusArgument>
#include <QDebug>
#include <QDateTime>

#include "global.h"

BEGIN_USER_NAMESPACE

namespace utils {
void registerAllMetaTypes();
}


enum TemperatureUnit {
    CELSIUS,
    FAHRENHEIT
};
struct Location {
    QString name;       // 地区/城市名
    QString id;         // 地区/城市ID
    double  latitude;   // 纬度
    double  longitude;  // 经度
    QString adm2;       // 地区/城市的上级行政区划名称
    QString adm1;       // 地区/城市所属一级行政区域
    QString country;    // 地区/城市所属国家名称
    QString timezone;   // 地区/城市所在时区
    QString utcOffset;  // 地区/城市目前与UTC时间偏移的小时数
    bool    isDst;      // 是否处于夏令时
    QString type;       // 城市类型
    
    static void registerMetaTypes();

    friend QDBusArgument        &operator<<(QDBusArgument &argument, const Location &data);
    friend const QDBusArgument  &operator>>(const QDBusArgument &argument, Location &data);
    friend QDebug               &operator<<(QDebug &debug, const Location &data);

};
struct CurrentWeather {
    Location        location;                                   // 该天气预报的城市或地区
    QDateTime       observedTime;                               // 该天气情况被观察到的时间
    TemperatureUnit temperatureUnit = TemperatureUnit::CELSIUS; // 当前温度单位
    double          temperature = 0.0;                          // 当前温度，默认摄氏度
    double          feelsLikeTemperature = 0.0;                 // 体感温度，默认摄氏度
    QString         iconName;                                   // 天气图标名，内部使用
    QString         description;                                // 天气描述
    double          wind360 = 0.0;                              // 360度风向
    QString         windDirection;                              // 风向
    double          windScale = 0.0;                            // 风力等级
    double          windSpeed = 0.0;                            // 风速
    double          humidity = 0.0;                             // 百分比湿度
    double          precip = 0.0;                               // 当前小时累计降水量
    double          pressure = 0.0;                             // 当前大气压强
    double          visibility = 0.0;                           // 能见度
    double          cloud = 0.0;                                // 云量，百分比数值，可能为空
    double          dew = 0.0;                                  // 露点温度，可能为空

    static void registerMetaTypes();

    void changeTemperatureUnit(TemperatureUnit unit);

    friend QDBusArgument        &operator<<(QDBusArgument &argument, const CurrentWeather &data);
    friend const QDBusArgument  &operator>>(const QDBusArgument &argument, CurrentWeather &data);
    friend QDebug               &operator<<(QDebug &debug, const CurrentWeather &data);

};


// enum WeatherOverview {
//     SUNNY,
//     RAINY,
//     CLOUDY,
//     WINDY,
//     SUNNY2RAINY,
//     SUNNY2CLOUDY,
//     CLOUDY2SUNNY,
//     RAINY2SUNNY
// };

// struct WeatherData {
//     WeatherOverview overview;
//     TemperatureUnit unit;
//     double          currentTemperature;
//     double          lowestTemperature;
//     double          highestTemperature;
//     QString         location;
    
//     static void registerMetaTypes();

//     WeatherData(
//         WeatherOverview overview = WeatherOverview::RAINY,
//         TemperatureUnit unit = TemperatureUnit::CELSIUS,
//         double currentTemperature = 0,
//         double lowestTemperature = 0,
//         double highestTemperature = 0,
//         QString location = ""
//         );
    
//     void changeTemperatureUnit(TemperatureUnit unit);

//     friend QDBusArgument        &operator<<(QDBusArgument &argument, const WeatherData &data);
//     friend const QDBusArgument  &operator>>(const QDBusArgument &argument, WeatherData &data);
//     friend QDebug               &operator<<(QDebug &debug, const WeatherData &data);
    
// };

inline double celsiusToFahrenheit(double celsius)
{
    return 9.0 / 5.0 * celsius + 32.0;
}

inline double fahrenheitToCelsius(double fahrenheit)
{
    return (5.0 / 9.0) * (fahrenheit - 32.0);
}

END_USER_NAMESPACE

Q_DECLARE_METATYPE(USER_NAMESPACE::Location)
Q_DECLARE_METATYPE(USER_NAMESPACE::CurrentWeather)
// Q_DECLARE_METATYPE(USER_NAMESPACE::WeatherData)
// Q_DECLARE_METATYPE(QList<USER_NAMESPACE::WeatherData>)
// Q_DECLARE_METATYPE(USER_NAMESPACE::WeatherOverview)
Q_DECLARE_METATYPE(USER_NAMESPACE::TemperatureUnit)
