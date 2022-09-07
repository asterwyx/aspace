// SPDX-FileCopyrightText: 2022 Astrea Wang
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>
#include <QApplication>
#include <sanitizer/asan_interface.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
#ifdef QT_DEBUG
    __sanitizer_set_report_path("asan_aspace.log");
#endif
    return ret;
}
