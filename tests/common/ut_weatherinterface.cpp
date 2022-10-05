#include <gtest/gtest.h>
#include "weatherinterface.h"

USE_USER_NAMESPACE
class WeatherInterfaceTest : public testing::Test
{
protected:
public:
    explicit WeatherInterfaceTest()
        : m_weatherInterface(new WeatherInterface(DBUS_SERVICE_NAME, DBUS_ASPACE_PATH, QDBusConnection::sessionBus()))
    {
    }

protected:
    WeatherInterface *m_weatherInterface;
};

TEST_F(WeatherInterfaceTest, LookForLocations)
{
    QList<Location> locations = m_weatherInterface->lookForLocations(QString::fromUtf8("武汉"));
    EXPECT_NE(locations.size(), 0);
}

TEST_F(WeatherInterfaceTest, GetCurrentWeather)
{
    CurrentWeather currentWeather = m_weatherInterface->getCurrentWeather("101010100");
    EXPECT_NE(currentWeather.observedTime.toString(), "");
    EXPECT_NE(currentWeather.temperature, -300);
}

TEST_F(WeatherInterfaceTest, GetFutureWeather)
{
    QList<FutureWeather> futureWeather = m_weatherInterface->getFutureWeather("101010100");
    EXPECT_EQ(futureWeather.size(), 3);
}

// TEST_F(WeatherInterfaceTest, CurrentWeatherUpdated)
//{
//     bool updated = false;
//     QObject::connect(m_weatherInterface, &WeatherInterface::currentWeatherUpdated, m_weatherInterface, [&] {
//         updated = true;
//     });
//     CurrentWeather currentWeather = m_weatherInterface->getCurrentWeather("101010100");
////    emit m_weatherInterface->currentWeatherUpdated(CurrentWeather());
//    EXPECT_TRUE(updated);
//}
//
// TEST_F(WeatherInterfaceTest, FutureWeatherUpdated)
//{
//    bool updated = false;
//    // wait for signal
//    QObject::connect(m_weatherInterface, &WeatherInterface::futureWeatherUpdated, m_weatherInterface, [&] {
//        updated = true;
//    });
//    QList<FutureWeather> futureWeather = m_weatherInterface->getFutureWeather("101010100");
////    emit m_weatherInterface->futureWeatherUpdated({});
//    EXPECT_TRUE(updated);
//}
