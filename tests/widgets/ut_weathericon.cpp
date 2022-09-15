#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "weathericon.h"
#include "weathericon_p.h"

USE_USER_NAMESPACE
TEST(WeatherIconTest, NullInit)
{
    WeatherIcon icon("");
    EXPECT_FALSE(icon.d_ptr->m_loaded);
}

TEST(WeatherIconTest, SetFromPath)
{
    WeatherIcon icon(":/icons/100.svg");
    EXPECT_TRUE(icon.d_ptr->m_loaded);
    EXPECT_THAT(icon.d_ptr->m_svgData, testing::NotNull());
}


TEST(WeatheIconTest, SetFromName)
{
    WeatherIcon icon;
    EXPECT_FALSE(icon.d_ptr->m_loaded);
    icon.setIconFromName("100");
    EXPECT_TRUE(icon.d_ptr->m_loaded);
    EXPECT_THAT(icon.d_ptr->m_svgData, testing::NotNull());
}