#include "weather.h"
#include <QApplication>
#include <QDebug>

USE_USER_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Weather w;
    qDebug() << w.getCurrentWeather();
    return a.exec();
}
