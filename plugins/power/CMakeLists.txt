# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

set(PLUGIN_NAME "power")

project(${PLUGIN_NAME})
#include_directories("widgets")
file(GLOB_RECURSE POWER_SRCS "*.cpp")
find_package(Qt5 REQUIRED COMPONENTS UiPlugin)

add_library(power SHARED ${POWER_SRCS})
target_link_libraries(power PRIVATE Qt5::Widgets Qt5::UiPlugin)
