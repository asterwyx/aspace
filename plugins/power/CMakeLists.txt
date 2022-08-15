# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

set(PLUGIN_NAME "power")

project(${PLUGIN_NAME})
file(GLOB POWER_SRCS ".h" "*.cpp")
find_package(Qt5 REQUIRED COMPONENTS UiPlugin)

add_library(${PLUGIN_NAME} SHARED ${POWER_SRCS})
target_link_libraries(${PLUGIN_NAME} PRIVATE Qt5::Widgets Qt5::UiPlugin)
install(TARGETS ${PLUGIN_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_PLUGINDIR})
