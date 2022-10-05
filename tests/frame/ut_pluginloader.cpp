#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "common_def.h"
#include "pluginloader.h"
#include "pluginloader_p.h"
#include <QScopedPointer>
#include "weatherplugin.h"
//#include <QDir>
#include "mainwindow.h"

USE_USER_NAMESPACE

class PluginLoaderTest : public testing::Test
{
public:
    PluginLoaderTest()
        : m_loader(new PluginLoader)
    {
    }

    ~PluginLoaderTest() { delete m_loader; }

protected:
    PluginLoader *m_loader;
};

TEST_F(PluginLoaderTest, GetPlugins)
{
    PluginInterface *plugin1 = new WeatherPlugin;
    PluginInterface *plugin2 = new WeatherPlugin;
    ASSERT_THAT(m_loader->d_ptr->m_plugins, testing::IsEmpty());
    m_loader->d_ptr->m_plugins.append(plugin1);
    auto *plugins = m_loader->getPlugins();
    EXPECT_THAT(*plugins, testing::SizeIs(1));
    EXPECT_EQ(plugins->front(), plugin1);
    m_loader->d_ptr->m_plugins.append(plugin2);
    EXPECT_THAT(*plugins, testing::SizeIs(2));
    EXPECT_EQ(plugins->front(), plugin1);
    EXPECT_EQ(plugins->back(), plugin2);
}

TEST_F(PluginLoaderTest, AddPluginDir)
{
    ASSERT_THAT(m_loader->d_ptr->m_pluginDirs, testing::IsEmpty());
    m_loader->addPluginDir("/usr/lib");
    EXPECT_THAT(m_loader->d_ptr->m_pluginDirs, testing::SizeIs(1));
    EXPECT_EQ(m_loader->d_ptr->m_pluginDirs[0], "/usr/lib");
    m_loader->addPluginDir("");
    EXPECT_THAT(m_loader->d_ptr->m_pluginDirs, testing::SizeIs(1));
    m_loader->addPluginDir("/usr/local/lib");
    EXPECT_THAT(m_loader->d_ptr->m_pluginDirs, testing::SizeIs(2));
    EXPECT_EQ(m_loader->d_ptr->m_pluginDirs[1], "/usr/local/lib");
}

TEST_F(PluginLoaderTest, LoadPlugins)
{
    m_loader->addPluginDir(PLUGIN_DIR);
    ASSERT_THAT(m_loader->d_ptr->m_plugins, testing::IsEmpty());
    MainWindow w;
    m_loader->loadPlugins(&w);
    w.initializeAllPlugins();
    EXPECT_NE(m_loader->d_ptr->m_plugins.size(), 0);
}