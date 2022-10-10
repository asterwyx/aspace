#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "common_def.h"
#include "mainwindow.h"
#include <QGSettings>
#include <QCoreApplication>
#include "weatherplugin.h"
#include "qwidgetmock.h"
#include "weathercontrollermock.h"
#include "stub.h"
#include "contentpage.h"

USE_USER_NAMESPACE

class ContentPageTest : public testing::Test
{
public:
    static void SetUpTestCase() { windowSettings = new QGSettings(SCHEMA_ID, SCHEMA_PATH); }

    static void TearDownTestCase()
    {
        delete windowSettings;
        windowSettings = nullptr;
    }

    ContentPageTest()
        : m_window{new MainWindow}
        , m_page(m_window->getContentPage().data())
    {
        m_window->show();
    }

    ~ContentPageTest() override { delete m_window; }

protected:
    MainWindow *m_window = nullptr;
    ContentPage *m_page = nullptr;

public:
    static QGSettings *windowSettings;
};

QGSettings *ContentPageTest::windowSettings = nullptr;

TEST_F(ContentPageTest, GetFrameSize)
{
    m_page->resize(1024, 1024);  // First resize it.
    QSize size = m_page->getFrameSize();
    EXPECT_EQ(1024, size.width());
    EXPECT_EQ(1024, size.height());
}

TEST_F(ContentPageTest, AddPlugin)
{
    PluginInterface *weatherPlugin1 = new WeatherPlugin;
    ASSERT_NE(nullptr, weatherPlugin1);
    m_page->addPlugin(weatherPlugin1);
    EXPECT_EQ(1, m_page->m_plugins.size());
    EXPECT_EQ(weatherPlugin1, m_page->m_plugins.front());
    m_page->addPlugin(nullptr);
    EXPECT_EQ(1, m_page->m_plugins.size());
    m_page->addPlugin(weatherPlugin1);
    EXPECT_EQ(2, m_page->m_plugins.size());
    EXPECT_EQ(weatherPlugin1, m_page->m_plugins.front());
    EXPECT_EQ(weatherPlugin1, m_page->m_plugins.back());
    delete weatherPlugin1;
}

TEST_F(ContentPageTest, Plugins)
{
    EXPECT_THAT(m_page->m_plugins, testing::IsEmpty());
    PluginInterface *plugin1 = new WeatherPlugin;
    PluginInterface *plugin2 = new WeatherPlugin;
    m_page->m_plugins << nullptr << plugin1 << plugin2;
    auto plugins = m_page->plugins();
    EXPECT_THAT(plugins, testing::SizeIs(3));
    EXPECT_THAT(plugins, testing::ElementsAre(nullptr, plugin1, plugin2));
    delete plugin1;
    delete plugin2;
}

TEST_F(ContentPageTest, AddItem)
{
    PluginInterface *plugin = new WeatherPlugin(m_page);
    plugin->initialize();
    EXPECT_THAT(m_page->m_itemMap, testing::SizeIs(2));
    // m_window->addItem(plugin, "");
    // EXPECT_THAT(m_window->m_itemMap, testing::SizeIs(1));
    // m_window->addItem(plugin, WeatherPlugin::CURRENT_WEATHER_ITEM);
    // EXPECT_THAT(m_window->m_itemMap, testing::SizeIs(1));
    // PluginInterface *plugin1 = new WeatherPlugin;
    // m_window->addItem(plugin1, WeatherPlugin::CURRENT_WEATHER_ITEM);
    // EXPECT_THAT(m_window->m_itemMap, testing::SizeIs(1));
    // m_window->addItem(plugin1, "test");
    // EXPECT_THAT(m_window->m_itemMap,testing::SizeIs(1));
    // m_window->addItem(plugin1, WeatherPlugin::FUTURE_WEATHER_ITEM);
    // EXPECT_THAT(m_window->m_itemMap,testing::SizeIs(2));
    delete plugin;
    // delete plugin1;
}

TEST_F(ContentPageTest, RemoveItem)
{
    EXPECT_THAT(m_page->m_itemMap, testing::IsEmpty());
    QWidget widget1, widget2, widget3;
    m_page->m_itemMap.insert("widget1", &widget1);
    m_page->m_itemMap.insert("null", nullptr);
    m_page->m_itemMap.insert("widget3", &widget3);
    m_page->m_itemMap.insert("widget2", &widget2);
    EXPECT_THAT(m_page->m_itemMap, testing::SizeIs(4));
    EXPECT_EQ(&widget1, m_page->m_itemMap["widget1"]);
    EXPECT_EQ(nullptr, m_page->m_itemMap["null"]);
    m_page->removeItem("widget1");
    EXPECT_THAT(m_page->m_itemMap, testing::SizeIs(3));
    EXPECT_FALSE(m_page->m_itemMap.contains("widget1"));
    m_page->removeItem("null");
    EXPECT_FALSE(m_page->m_itemMap.contains("null"));
    m_page->removeItem("widget2");
    m_page->removeItem("widget3");
    EXPECT_THAT(m_page->m_itemMap, testing::IsEmpty());
}

TEST_F(ContentPageTest, UpdateItem)
{
    class MockWidget : public QWidget
    {
    public:
        bool updated = false;

    protected:
        void paintEvent(QPaintEvent *event) override
        {
            Q_UNUSED(event);
            qDebug() << "Item Widget is updated.";
            updated = true;
        }
    };
    MockWidget widget;
    ASSERT_FALSE(widget.updated);
    m_page->m_itemMap.insert("test-widget", &widget);
    ASSERT_FALSE(widget.updated);
    //    widget.show();
    //    EXPECT_TRUE(widget.updated);
    //    widget.updated = false;
    Stub stub;
    stub.set((void(QWidget::*)()) & QWidget::update, updateStub);
    m_page->updateItem("test-widget");
    //    QCoreApplication::sendPostedEvents();
    EXPECT_TRUE(widget.updated);
}

TEST_F(ContentPageTest, InitializeAllPlugins)
{
    PluginInterface *plugin1 = new WeatherPlugin;
    plugin1->setFrameProxy(m_page);
    m_page->m_plugins.push_back(plugin1);
    m_page->initializeAllPlugins();
    EXPECT_THAT(m_page->m_itemMap, testing::SizeIs(2));
    delete plugin1;
}

TEST_F(ContentPageTest, PluginAdded)
{
    EXPECT_THAT(m_page->m_plugins, testing::IsEmpty());
    PluginInterface *plugin = new WeatherPlugin;
    m_page->pluginAdded(plugin);
    EXPECT_THAT(m_page->m_plugins, testing::SizeIs(1));
    delete plugin;
}

TEST_F(ContentPageTest, LoadData)
{
    bool currentUpdated = false;
    bool futureUpdated = false;
    auto *plugin = new WeatherPlugin;
    Stub stub;
    m_page->addPlugin(plugin);
    plugin->initialize();
    stub.set(ADDR(WeatherController, updateCurrentWeather), updateCurrentWeatherStub);
    stub.set(ADDR(WeatherController, updateFutureWeather), updateFutureWeatherStub);
    QObject::connect(plugin->m_controller->m_currentWeatherModel.data(),
                     &CurrentWeatherModel::currentWeatherChanged,
                     m_page,
                     [&] { currentUpdated = true; });
    QObject::connect(plugin->m_controller->m_futureWeatherModel.data(), &FutureWeatherModel::dataChanged, m_page, [&] {
        futureUpdated = true;
    });
    m_page->loadData();
    EXPECT_TRUE(currentUpdated);
    EXPECT_TRUE(futureUpdated);
}