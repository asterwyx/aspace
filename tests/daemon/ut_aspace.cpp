#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "common_def.h"
#include "aspace.h"

USE_USER_NAMESPACE

class AspaceTest : public testing::Test {
public:

    AspaceTest() : m_aspace(new Aspace) {}
    
    ~AspaceTest() { delete m_aspace; }

    static void SetUpTestCase()
    {
        utils::registerAllMetaTypes();
    }
protected:
    Aspace  *m_aspace;
};

TEST_F(AspaceTest, ApiKey)
{
    const char *key = m_aspace->apiKey();
    EXPECT_STREQ(key, "b3aeb3cb72a74857b66a1f423c15bb89");
}

TEST_F(AspaceTest, LookForLocations)
{
    bool ok = false;
    QList<Location> locations = m_aspace->lookForLocations(QString::fromUtf8("武汉"), &ok);
    EXPECT_TRUE(ok);
    EXPECT_NE(locations.size(), 0);
}

TEST_F(AspaceTest, GetCurrentWeather)
{
    bool ok = false;
    CurrentWeather currentWeather = m_aspace->getCurrentWeather("101010100", &ok);
    EXPECT_TRUE(ok);
    EXPECT_NE(currentWeather.observedTime.toString(), "");
}

TEST_F(AspaceTest, GetFutureWeather)
{
    bool ok = false;
    QList<FutureWeather> futureWeather = m_aspace->getFutureWeather("101010100", &ok);
    EXPECT_TRUE(ok);
    EXPECT_EQ(futureWeather.size(), 3);
}