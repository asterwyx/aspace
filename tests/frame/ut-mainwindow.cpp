//
// Created by astrea on 9/7/22.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "common_def.h"
#include "mainwindow.h"
#include <QGSettings>
#include <QCoreApplication>
#include "weatherplugin.h"
#include "qwidgetmock.h"


USE_USER_NAMESPACE

class MainWindowTest : public testing::Test {

public:

    static void SetUpTestCase() {
        windowSettings = new QGSettings(SCHEMA_ID, SCHEMA_PATH);
    }

    static void TearDownTestCase() {
        delete windowSettings;
        windowSettings = nullptr;
    }

    MainWindowTest() : m_window{new MainWindow} {}

    ~MainWindowTest() override { delete m_window; }

protected:
    MainWindow *m_window = nullptr;

public:
    static QGSettings *windowSettings;
};

QGSettings *MainWindowTest::windowSettings = nullptr;


TEST_F(MainWindowTest, MinimumSize)
{
    // We have hard coded the minimum size to 200, 200
    QSize size = m_window->minimumSize();
    EXPECT_EQ(200, size.width());
    EXPECT_EQ(200, size.height());
}

TEST_F(MainWindowTest, GetFrameSize)
{
    m_window->resize(1024, 1024); // First resize it.
    QSize size = m_window->getFrameSize();
    EXPECT_EQ(1024, size.width());
    EXPECT_EQ(1024, size.height());
}

TEST_F(MainWindowTest, LoadDefaultSize)
{
    // We have specified a default value in gsettings config
    bool ok = false;
    int width = windowSettings->get("window-width").toInt(&ok);
    ASSERT_TRUE(ok);
    int height = windowSettings->get("window-height").toInt(&ok);
    ASSERT_TRUE(ok);
    m_window->loadDefaultSize();
    EXPECT_EQ(width, m_window->width());
    EXPECT_EQ(height, m_window->height());
}

TEST_F(MainWindowTest, AddPlugin) {
    PluginInterface *weatherPlugin1 = new WeatherPlugin;
    ASSERT_NE(nullptr, weatherPlugin1);
    m_window->addPlugin(weatherPlugin1);
    EXPECT_EQ(1, m_window->m_plugins.size());
    EXPECT_EQ(weatherPlugin1, m_window->m_plugins.front());
    m_window->addPlugin(nullptr);
    EXPECT_EQ(1, m_window->m_plugins.size());
    m_window->addPlugin(weatherPlugin1);
    EXPECT_EQ(2, m_window->m_plugins.size());
    EXPECT_EQ(weatherPlugin1, m_window->m_plugins.front());
    EXPECT_EQ(weatherPlugin1, m_window->m_plugins.back());
    delete weatherPlugin1;
}

TEST_F(MainWindowTest, Plugins)
{
    EXPECT_THAT(m_window->m_plugins, testing::IsEmpty());
    PluginInterface *plugin1 = new WeatherPlugin;
    PluginInterface *plugin2 = new WeatherPlugin;
    m_window->m_plugins << nullptr << plugin1 << plugin2;
    auto plugins = m_window->plugins();
    EXPECT_THAT(plugins, testing::SizeIs(3));
    EXPECT_THAT(plugins, testing::ElementsAre(nullptr, plugin1, plugin2));
    delete plugin1;
    delete plugin2;
}

TEST_F(MainWindowTest, AddItem)
{
    PluginInterface *plugin = new WeatherPlugin(m_window);
    plugin->preInitialize();
    plugin->initialize();
    EXPECT_THAT(m_window->m_itemMap, testing::SizeIs(1));
    m_window->addItem(plugin, "");
    EXPECT_THAT(m_window->m_itemMap, testing::SizeIs(1));
    m_window->addItem(plugin, WeatherPlugin::CURRENT_WEATHER_ITEM);
    EXPECT_THAT(m_window->m_itemMap, testing::SizeIs(1));
    PluginInterface *plugin1 = new WeatherPlugin;
    m_window->addItem(plugin1, WeatherPlugin::CURRENT_WEATHER_ITEM);
    EXPECT_THAT(m_window->m_itemMap, testing::SizeIs(1));
    m_window->addItem(plugin1, "test");
    EXPECT_THAT(m_window->m_itemMap,testing::SizeIs(1));
    m_window->addItem(plugin1, WeatherPlugin::FUTURE_WEATHER_ITEM);
    EXPECT_THAT(m_window->m_itemMap,testing::SizeIs(2));
    delete plugin;
    delete plugin1;
}

TEST_F(MainWindowTest, RemoveItem)
{
    EXPECT_THAT(m_window->m_itemMap, testing::IsEmpty());
    QWidget widget1, widget2, widget3;
    m_window->m_itemMap.insert("widget1", &widget1);
    m_window->m_itemMap.insert("null", nullptr);
    m_window->m_itemMap.insert("widget3", &widget3);
    m_window->m_itemMap.insert("widget2", &widget2);
    EXPECT_THAT(m_window->m_itemMap, testing::SizeIs(4));
    EXPECT_EQ(&widget1, m_window->m_itemMap["widget1"]);
    EXPECT_EQ(nullptr, m_window->m_itemMap["null"]);
    m_window->removeItem("widget1");
    EXPECT_THAT(m_window->m_itemMap, testing::SizeIs(3));
    EXPECT_FALSE(m_window->m_itemMap.contains("widget1"));
    m_window->removeItem("null");
    EXPECT_FALSE(m_window->m_itemMap.contains("null"));
    m_window->removeItem("widget2");
    m_window->removeItem("widget3");
    EXPECT_THAT(m_window->m_itemMap, testing::IsEmpty());
}

TEST_F(MainWindowTest, UpdateItem)
{
    class MockWidget : public QWidget {
    public:
        bool updated = false;
    protected:
        void paintEvent(QPaintEvent *event) override {
            Q_UNUSED(event);
            qDebug() << "Item Widget is updated.";
            updated = true;
        }
    };
    MockWidget widget;
    ASSERT_FALSE(widget.updated);
    m_window->m_itemMap.insert("test-widget", &widget);
    ASSERT_FALSE(widget.updated);
    setMocked(true);
    m_window->updateItem("test-widget");
    EXPECT_TRUE(widget.updated);
    setMocked(false);
}