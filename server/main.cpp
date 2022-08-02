#include "pluginloader.h"
#include <QApplication>
#include <QMainWindow>
using namespace dspace;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QMainWindow w;
  PluginLoader loader("plugins/echoeditor");
  loader.loadPlugins();
  loader.showAllPlugins(&w);
  w.show();
  return a.exec();
}