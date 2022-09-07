//
// Created by astrea on 9/7/22.
//

#include <gtest/gtest.h>
#include "common_def.h"
#include "mainwindow.h"

USE_USER_NAMESPACE

class MainWindowTest : public testing::Test {
public:
    explicit MainWindowTest(MainWindow *mWindow = nullptr, QGSettings *mWindowSettings = nullptr);

    void SetUp() override
    {
        m_window = new MainWindow;
    }

    void TearDown() override {
        delete m_window;
        m_window = nullptr;
    }

public:
    MainWindow *m_window = nullptr;
    QGSettings *m_windowSettings = nullptr;
};

MainWindowTest::MainWindowTest(MainWindow *mWindow, QGSettings *mWindowSettings)
    : testing::Test(),
    m_window(mWindow),
    m_windowSettings(mWindowSettings) {}


TEST_F(MainWindowTest, MinimumSize)
{
    // We have hard coded the minimum size to 200, 200
    QSize size = m_window->minimumSize();
    EXPECT_EQ(200, size.width());
    EXPECT_EQ(200, size.height());
}

TEST_F(MainWindowTest, GetFrameSize)
{
    m_window->resize(1024, 1024);
    QSize size = m_window->getFrameSize();
    EXPECT_EQ(1024, size.width());
    EXPECT_EQ(1024, size.height());
}

TEST_F(MainWindowTest, LoadDefaultSize)
{

}