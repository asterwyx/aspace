# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

project(aspace-unit-test
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "A space for weather and rest."
    VERSION ${VERSION})

find_package(GTest REQUIRED COMPONENTS GTest Main)

aux_source_directory("." TEST_SRCS)

link_directories(
    "../plugins/echoeditor"
    "../plugins/weather"
    "../plugins/power"
    "../widgets"
)

add_executable(aspace-unit-test ${TEST_SRCS})

target_link_libraries(aspace-unit-test PRIVATE
    Qt::Widgets
    Qt::UiPlugin
    GTest::GTest
    GTest::Main
    widgets
    )
