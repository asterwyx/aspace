// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>
#include <QApplication>
#include "weatherdata.h"
USE_USER_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    utils::registerAllMetaTypes();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
