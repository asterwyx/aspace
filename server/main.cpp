#include "pluginloader.h"
#include <QApplication>
#include <QMainWindow>
using namespace dspace;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QMainWindow w;
  PluginLoader loader("plugins/weather");
  loader.addPluginDir("plugins/echoeditor");
  loader.loadPlugins();
  loader.showAllPlugins(&w);
  w.resize(400, 200);
  w.show();
  return a.exec();
}