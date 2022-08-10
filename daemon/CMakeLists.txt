# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

project(aspace-daemon
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "Daemon server binary."
    VERSION 1.0.0)

file(GLOB DAEMON_SRCS "*.h" "*.cpp" "*.qrc")

add_executable(aspace-daemon ${DAEMON_SRCS})
target_link_libraries(aspace-daemon PRIVATE
    Qt5::Widgets
    Qt5::DBus
    common
    )
