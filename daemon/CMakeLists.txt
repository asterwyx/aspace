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

install(TARGETS aspace-daemon RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
set(DAEMON_BIN "${CMAKE_INSTALL_BINDIR}/aspace-daemon")
configure_file(org.deepin.aspace.service.in "${DBUS_SERVICE_NAME}.service")
install(FILES "${DBUS_SERVICE_NAME}.service" DESTINATION ${CMAKE_INSTALL_DBUSDIR})
