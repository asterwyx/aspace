# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

project(aspace-daemon
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "Daemon server binary."
    VERSION 1.0.0)

file(GLOB DAEMON_SRCS "*.h" "*.cpp")

add_executable(aspace-daemon ${DAEMON_SRCS})
target_link_libraries(aspace-daemon PRIVATE
    Qt5::Widgets
    Qt5::DBus
    ${ASPACE_COMMON}
)

install(TARGETS aspace-daemon RUNTIME)
set(DAEMON_BIN "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}/aspace-daemon")

configure_file(org.deepin.aspace.service.in "${DBUS_SERVICE_NAME}.service")
install(FILES "${PROJECT_BINARY_DIR}/${DBUS_SERVICE_NAME}.service" DESTINATION ${CMAKE_INSTALL_DBUSDIR})

configure_file(aspace.service.in "${CLIENT_NAME}.service")
install(FILES "${PROJECT_BINARY_DIR}/${CLIENT_NAME}.service" DESTINATION ${CMAKE_INSTALL_SYSTEMDDIR})