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
#include <QStackedLayout>
#include "loadingpage.h"
#include "contentpage.h"
#include <DTitlebar>

USE_USER_NAMESPACE

class MainWindowTest : public testing::Test
{
public:
    static void SetUpTestCase() { windowSettings = new QGSettings(SCHEMA_ID, SCHEMA_PATH); }

    static void TearDownTestCase()
    {
        delete windowSettings;
        windowSettings = nullptr;
    }

    MainWindowTest()
        : m_window{new MainWindow}
    {
        m_window->show();
    }

    ~MainWindowTest() override { delete m_window; }

protected:
    MainWindow *m_window = nullptr;

public:
    static QGSettings *windowSettings;
};

QGSettings *MainWindowTest::windowSettings = nullptr;

TEST_F(MainWindowTest, showContents)
{
    m_window->m_stackedLayout->setCurrentWidget(m_window->m_loadingPage);
    m_window->showContents();
    EXPECT_EQ(m_window->m_stackedLayout->currentWidget(), reinterpret_cast<QWidget *>(m_window->m_contentPage));
}

TEST_F(MainWindowTest, showSplash)
{
    m_window->m_stackedLayout->setCurrentWidget(m_window->m_contentPage);
    m_window->showSplash();
    EXPECT_EQ(m_window->m_stackedLayout->currentWidget(), reinterpret_cast<QWidget *>(m_window->m_loadingPage));
}

TEST_F(MainWindowTest, showSelect)
{
    m_window->m_stackedLayout->setCurrentWidget(m_window->m_contentPage);
    m_window->showSelect();
    EXPECT_EQ(m_window->m_stackedLayout->currentWidget(), reinterpret_cast<QWidget *>(m_window->m_selectingPage));
}

TEST_F(MainWindowTest, GetWindowSettings)
{
    EXPECT_EQ(m_window->getWindowSettings(), m_window->m_windowSettings);
}

// TEST_F(MainWindowTest, Refresh)
// {
//     bool currentUpdated = false;
//     bool futureUpdated = false;
//     auto *plugin = new WeatherPlugin;
//     Stub stub;
//     m_window->m_contentPage->addPlugin(plugin);
//     plugin->initialize();
//     stub.set(ADDR(WeatherController, updateCurrentWeather), updateCurrentWeatherStub);
//     stub.set(ADDR(WeatherController, updateFutureWeather), updateFutureWeatherStub);
//     QObject::connect(plugin->m_controller->m_currentWeatherModel.data(),
//                      &CurrentWeatherModel::currentWeatherChanged,
//                      m_window,
//                      [&] { currentUpdated = true; });
//     QObject::connect(plugin->m_controller->m_futureWeatherModel.data(), &FutureWeatherModel::dataChanged, m_window, [&] {
//         futureUpdated = true;
//     });
//     m_window->refresh();
//     EXPECT_TRUE(currentUpdated);
//     EXPECT_TRUE(futureUpdated);
// }

TEST_F(MainWindowTest, ResizeEvent)
{
    m_window->resize(1024, 1024);
    EXPECT_EQ(m_window->width(), m_window->m_contentFrame->width());
    EXPECT_EQ(m_window->height() - m_window->titlebar()->height(), m_window->m_contentFrame->height());
    m_window->resize(512, 512);
    EXPECT_EQ(m_window->width(), m_window->m_contentFrame->width());
    EXPECT_EQ(m_window->height() - m_window->titlebar()->height(), m_window->m_contentFrame->height());
    // Try using QTest to simulate resize event to test resizeEvent function
}

// TEST_F(MainWindowTest, SetSizeQSize)
// {
//     bool ok = false;
//     int width = windowSettings->get("window-width").toInt(&ok);
//     ASSERT_TRUE(ok);
//     int height = windowSettings->get("window-height").toInt(&ok);
//     ASSERT_TRUE(ok);
//     m_window->setSize({width + 100, height + 100});
//     int newWidth = windowSettings->get("window-width").toInt(&ok);
//     ASSERT_TRUE(ok);
//     int newHeight = windowSettings->get("window-height").toInt(&ok);
//     ASSERT_TRUE(ok);
//     EXPECT_EQ(width + 100, newWidth);
//     EXPECT_EQ(height + 100, newHeight);
//     windowSettings->set("window-width", width);
//     windowSettings->set("window-height", height);
// }

// TEST_F(MainWindowTest, SetSize)
// {
//     bool ok = false;
//     int width = windowSettings->get("window-width").toInt(&ok);
//     ASSERT_TRUE(ok);
//     int height = windowSettings->get("window-height").toInt(&ok);
//     ASSERT_TRUE(ok);
//     m_window->setSize(width + 100, height + 100);
//     int newWidth = windowSettings->get("window-width").toInt(&ok);
//     ASSERT_TRUE(ok);
//     int newHeight = windowSettings->get("window-height").toInt(&ok);
//     ASSERT_TRUE(ok);
//     EXPECT_EQ(width + 100, newWidth);
//     EXPECT_EQ(height + 100, newHeight);
//     windowSettings->set("window-width", width);
//     windowSettings->set("window-height", height);
// }

// TEST_F(MainWindowTest, SetSaveLastWindowSize)
// {
//     bool ok = false;
//     int width = windowSettings->get("window-width").toInt(&ok);
//     ASSERT_TRUE(ok);
//     int height = windowSettings->get("window-height").toInt(&ok);
//     ASSERT_TRUE(ok);
//     bool originalSetting = windowSettings->get("save-window-size").toBool();
//     if (originalSetting)
//     {
//         m_window->setSaveLastWindowSize(false);
//         m_window->resize(width, height);
//         m_window->resize(width + 100, height + 100);
//         delete m_window;
//         int newWidth = windowSettings->get("window-width").toInt(&ok);
//         ASSERT_TRUE(ok);
//         int newHeight = windowSettings->get("window-height").toInt(&ok);
//         ASSERT_TRUE(ok);
//         EXPECT_EQ(width, newWidth);
//         EXPECT_EQ(height, newHeight);
//         m_window = new MainWindow;
//         m_window->setSaveLastWindowSize(true);
//         m_window->resize(width, height);
//         m_window->resize(width + 100, height + 100);
//         delete m_window;
//         m_window = nullptr;
//         newWidth = windowSettings->get("window-width").toInt(&ok);
//         ASSERT_TRUE(ok);
//         newHeight = windowSettings->get("window-height").toInt(&ok);
//         ASSERT_TRUE(ok);
//         EXPECT_EQ(width + 100, newWidth);
//         EXPECT_EQ(height + 100, newHeight);
//     }
//     else
//     {
//         // original is false
//         qDebug() << "Original is false.";
//         m_window->setSaveLastWindowSize(true);
//         m_window->resize(width, height);
//         m_window->resize(width + 100, height + 100);
//         delete m_window;
//         int newWidth = windowSettings->get("window-width").toInt(&ok);
//         ASSERT_TRUE(ok);
//         int newHeight = windowSettings->get("window-height").toInt(&ok);
//         ASSERT_TRUE(ok);
//         EXPECT_EQ(width + 100, newWidth);
//         EXPECT_EQ(height + 100, newHeight);
//         m_window = new MainWindow;
//         width = windowSettings->get("window-width").toInt(&ok);
//         ASSERT_TRUE(ok);
//         height = windowSettings->get("window-height").toInt(&ok);
//         ASSERT_TRUE(ok);
//         m_window->setSaveLastWindowSize(false);
//         m_window->resize(width, height);
//         m_window->resize(width + 100, height + 100);
//         delete m_window;
//         m_window = nullptr;
//         newWidth = windowSettings->get("window-width").toInt(&ok);
//         ASSERT_TRUE(ok);
//         newHeight = windowSettings->get("window-height").toInt(&ok);
//         ASSERT_TRUE(ok);
//         EXPECT_EQ(width, newWidth);
//         EXPECT_EQ(height, newHeight);
//     }
//     windowSettings->set("save-window-size", originalSetting);
// }

// TEST_F(MainWindowTest, SaveWindowSize)
// {
//     bool saveWindowSize = windowSettings->get("save-window-size").toBool();
//     EXPECT_EQ(saveWindowSize, m_window->saveLastWindowSize());
// }

// TEST_F(MainWindowTest, SetSaveWindowSize)
// {
//     bool originSetting = windowSettings->get("save-window-size").toBool();
//     if (originSetting)
//     {
//         // true, set false
//         m_window->setSaveLastWindowSize(false);
//         bool nowSetting = windowSettings->get("save-window-size").toBool();
//         EXPECT_FALSE(nowSetting);
//     }
//     else
//     {
//         // false, set true
//         m_window->setSaveLastWindowSize(true);
//         bool nowSetting = windowSettings->get("save-window-size").toBool();
//         EXPECT_TRUE(nowSetting);
//     }
// }