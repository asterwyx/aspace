# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

project(${DAEMON}
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "Daemon server binary."
    VERSION 1.0.0)

file(GLOB_RECURSE DAEMON_SRCS "*.h" "*.cpp" "*.qrc")

add_executable(${DAEMON}
    ${DAEMON_SRCS}
    )

target_link_libraries(${DAEMON} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Xml
    ${DtkCore_LIBRARIES}
    ${COMMON}
)

install(TARGETS ${DAEMON} RUNTIME)