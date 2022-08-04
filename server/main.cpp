#include "pluginloader.h"
#include <QApplication>
#include <QMainWindow>

#include "dynamicsun.h"
using namespace dspace;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QMainWindow w;
//    PluginLoader loader("plugins/power");
//    loader.addPluginDir("plugins/weather");
//    loader.addPluginDir("plugins/echoeditor");
//    loader.loadPlugins();
    auto sun = new DynamicSun(&w);
//    [[maybe_unused]] auto battery = new Battery(&w);
    sun->move(50,50);
//    loader.showAllPlugins(&w);
    w.resize(400, 200);
    w.show();
    return a.exec();
}
