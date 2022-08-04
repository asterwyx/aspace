#include <gtest/gtest.h>
#include "battery.h"
#include <QMainWindow>
#include <QApplication>

namespace dspace {
TEST(test_widget_battery, DefaultConstrutor)
{
    int argc = 0;
    QApplication a(argc, nullptr);
    QMainWindow w;
    Battery *battery = new Battery();
    battery->setParent(&w);
    w.show();
    a.exec();
}
}