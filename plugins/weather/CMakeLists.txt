# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

set(PLUGIN_NAME "weather")

project(${PLUGIN_NAME})
file(GLOB WEATHER_SRCS "*.h" "*.cpp" "*.qrc")
find_package(Qt5 REQUIRED COMPONENTS DBus Concurrent)
add_library(weather SHARED ${WEATHER_SRCS})
target_link_libraries(weather PRIVATE
    Qt5::Widgets
    Qt5::DBus
    Qt5::Concurrent
    widgets
    common
    )
