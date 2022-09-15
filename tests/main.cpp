// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>
#include <QApplication>
#include <QTimer>
#include "utils.h"
USE_USER_NAMESPACE

int runTests(QCoreApplication &app)
{
    int ret = 1;
    QTimer::singleShot(0, &app, [&app, &ret] {
        ret = RUN_ALL_TESTS();
        app.quit();
    });
    app.exec();
    return ret;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Utils::registerAllMetaTypes();
    testing::InitGoogleTest(&argc, argv);
    return runTests(app);
}
