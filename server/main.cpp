#include "pluginloader.h"
#include <QApplication>
#include <QMainWindow>
using namespace dspace;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    w.show();
    dspace::PluginLoader loader("plugins");
    loader.loadPlugins();
    loader.showAllPlugins();
    return a.exec();
}