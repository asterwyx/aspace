# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

set(PLUGIN_NAME "echo-editor")

project(${PLUGIN_NAME})
file(GLOB ECHO_EDITOR_SRCS ".h" "*.cpp")

add_library(${PLUGIN_NAME} SHARED ${ECHO_EDITOR_SRCS})
target_link_libraries(${PLUGIN_NAME} PRIVATE Qt5::Widgets)
install(TARGETS ${PLUGIN_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_PLUGINDIR})