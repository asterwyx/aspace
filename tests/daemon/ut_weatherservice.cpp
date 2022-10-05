#include <gtest/gtest.h>
#include "weatherservice.h"
#include "aspace.h"
USE_USER_NAMESPACE

class WeatherServiceTest : public testing::Test
{
public:
    WeatherServiceTest()
        : m_aspace(new Aspace)
        , m_service(new WeatherService(m_aspace))
    {
    }
    ~WeatherServiceTest() override { delete m_aspace; }

protected:
    Aspace *m_aspace;
    WeatherService *m_service;
};

TEST_F(WeatherServiceTest, TestContext)
{
    EXPECT_EQ(m_service->context(), m_aspace);
}

TEST_F(WeatherServiceTest, LookForLocations)
{
    QList<Location> locations = m_service->lookForLocations(QString::fromUtf8("武汉"));
    EXPECT_NE(locations.size(), 0);
}

TEST_F(WeatherServiceTest, GetCurrentWeather)
{
    CurrentWeather currentWeather = m_service->getCurrentWeather("101010100");
    EXPECT_NE(currentWeather.observedTime.toString(), "");
    EXPECT_NE(currentWeather.temperature, -300);
}

TEST_F(WeatherServiceTest, GetFutureWeather)
{
    QList<FutureWeather> futureWeather = m_service->getFutureWeather("101010100");
    EXPECT_EQ(futureWeather.size(), 3);
}

TEST_F(WeatherServiceTest, CurrentWeatherUpdated)
{
    bool updated = false;
    QObject::connect(m_service, &WeatherService::currentWeatherUpdated, m_service, [&] { updated = true; });
    emit m_service->currentWeatherUpdated(CurrentWeather());
    EXPECT_TRUE(updated);
}

TEST_F(WeatherServiceTest, FutureWeatherUpdated)
{
    bool updated = false;
    QObject::connect(m_service, &WeatherService::futureWeatherUpdated, m_service, [&] { updated = true; });
    emit m_service->futureWeatherUpdated({});
    EXPECT_TRUE(updated);
}