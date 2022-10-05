#include <gtest/gtest.h>
#include "controllers/weathercontroller.h"
#include "models/currentweathermodel.h"
USE_USER_NAMESPACE

class WeatherControllerTest : public testing::Test
{
public:
    WeatherControllerTest()
    {
        m_controller = new WeatherController;
        m_controller->m_locationModel->m_location.id = "101010100";
    }

    ~WeatherControllerTest() override { delete m_controller; }

protected:
    QString m_id = "101010100";
    WeatherController *m_controller;
};

TEST_F(WeatherControllerTest, SetLocation)
{
    ASSERT_EQ(m_controller->getLocationModel()->getLocationId(), QStringLiteral("101010100"));
    Location location;
    location.id = "abcdefg";
    location.name = "hijklmn";
    m_controller->setLocation(location);
    EXPECT_EQ(m_controller->getLocationModel()->getLocationId(), QStringLiteral("abcdefg"));
    EXPECT_EQ(m_controller->getLocationModel()->getLocation().name, QStringLiteral("hijklmn"));
}

TEST_F(WeatherControllerTest, UpdateCurrentWeather)
{
    bool updated = false;
    QObject::connect(m_controller->getCurrentWeatherModel().data(),
                     &CurrentWeatherModel::currentWeatherChanged,
                     m_controller,
                     [&] { updated = true; });
    m_controller->updateCurrentWeather();
    EXPECT_TRUE(updated);
}

TEST_F(WeatherControllerTest, UpdateFutureWeather)
{
    bool updated = false;
    QObject::connect(
        m_controller->getFutureWeatherModel().data(), &FutureWeatherModel::dataChanged, m_controller, [&] { updated = true; });
    m_controller->updateFutureWeather();
    EXPECT_TRUE(updated);
}

TEST_F(WeatherControllerTest, GetUpdateTime)
{
    m_controller->m_updateTime = QDateTime::currentDateTime();
    EXPECT_EQ(m_controller->m_updateTime, m_controller->getUpdateTime());
}

TEST_F(WeatherControllerTest, LookForLocations)
{
    QList<Location> locations = m_controller->lookForLocations(QString::fromUtf8("武汉"));
    EXPECT_NE(locations.size(), 0);
}

TEST_F(WeatherControllerTest, GetCurrentWeatherModel)
{
    EXPECT_EQ(m_controller->getCurrentWeatherModel(), m_controller->m_currentWeatherModel);
}

TEST_F(WeatherControllerTest, SetCurrentWeatherModel)
{
    auto *model = new CurrentWeatherModel;
    m_controller->setCurrentWeatherModel(model);
    EXPECT_EQ(m_controller->m_currentWeatherModel.data(), model);
}

TEST_F(WeatherControllerTest, GetFutureWeatherModel)
{
    EXPECT_EQ(m_controller->getFutureWeatherModel(), m_controller->m_futureWeatherModel);
}

TEST_F(WeatherControllerTest, SetFutureWeatherModel)
{
    auto *model = new FutureWeatherModel(nullptr);
    m_controller->setFutureWeatherModel(model);
    EXPECT_EQ(m_controller->m_futureWeatherModel.data(), model);
}

TEST_F(WeatherControllerTest, GetLocationModel)
{
    EXPECT_EQ(m_controller->getLocationModel(), m_controller->m_locationModel);
}

TEST_F(WeatherControllerTest, SetLocationModel)
{
    auto *model = new LocationModel;
    m_controller->setLocationModel(model);
    EXPECT_EQ(m_controller->m_locationModel.data(), model);
}
