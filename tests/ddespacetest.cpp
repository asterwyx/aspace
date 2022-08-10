// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>
#include "battery.h"
#include <QMainWindow>
#include <QApplication>
#include "namespace.h"

USE_USER_NAMESPACE

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
