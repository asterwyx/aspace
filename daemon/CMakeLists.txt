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
    ${DtkCore_LIBRARIES}
    ${COMMON}
)

install(TARGETS ${DAEMON} RUNTIME)
set(DAEMON_BIN "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}/${DAEMON}")

configure_file(org.deepin.aspace.service.in "${DBUS_SERVICE_NAME}.service")
install(FILES "${PROJECT_BINARY_DIR}/${DBUS_SERVICE_NAME}.service" DESTINATION ${CMAKE_INSTALL_DBUSDIR})

configure_file(aspace.service.in "${CLIENT}.service")
install(FILES "${PROJECT_BINARY_DIR}/${CLIENT}.service" DESTINATION ${CMAKE_INSTALL_SYSTEMDDIR})

configure_file(update-weather.timer.in update-weather.timer)
install(FILES "${PROJECT_BINARY_DIR}/update-weather.timer" DESTINATION ${CMAKE_INSTALL_SYSTEMDDIR})