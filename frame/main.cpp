//#include "pluginloader.h"
#include <QApplication>
#include <QMainWindow>

//#include "dynamicsun.h"
#include "weathericon.h"
USE_USER_NAMESPACE

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QMainWindow w;
//    PluginLoader loader("plugins/power");
//    loader.addPluginDir("plugins/weather");
//    loader.addPluginDir("plugins/echoeditor");
//    loader.loadPlugins();
//    auto sun = new DynamicSun(&w);
//    [[maybe_unused]] auto battery = new Battery(&w);
//    sun->move(10,10);
//    sun->resize(70,70);
//    loader.showAllPlugins(&w);
    auto sunnyIcon = new WeatherIcon(":/100.svg", 9);
    sunnyIcon->setParent(&w);
    sunnyIcon->setSvgColor();
    w.resize(800, 800);
    w.show();
    return a.exec();
}
