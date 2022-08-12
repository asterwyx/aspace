# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.7)

if (NOT DEFINED VERSION)
    set(VERSION "1.0.0")
endif()

project(aspace
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "A space for weather and rest."
    VERSION ${VERSION})


if (NOT DEFINED DBUS_SERVICE_NAME)
    set(DBUS_SERVICE_NAME "org.deepin.aspace")
endif()
add_compile_definitions("-D${DBUS_SERVICE_NAME}")
message(STATUS $ENV{HOME})
set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local")
set(CMAKE_INSTALL_BINDIR "bin")
set(CMAKE_INSTALL_LIBDIR "lib/aspace")
set(CMAKE_INSTALL_SCHEMADIR "/usr/share/glib-2.0/schemas")
set(CMAKE_INSTALL_DBUSDIR "share/dbus-1/services")
set(CMAKE_INSTALL_SYSTEMDDIR "/etc/systemd/user")
set(CMAKE_INSTALL_ENTRYDIR "share/applications")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(GNUInstallDirs)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fPIC -Wall -Wextra")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -Wl,--as-needed")

# find qt related package
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui UiPlugin LinguistTools Svg DBus)
set(TS_FILES translations/aspace_zh_CN.ts)
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

# export include directories and link directories for gtest use
include_directories(
    "interfaces"
    "widgets"
    "common"
    )
link_directories(
    "plugins/echoeditor"
    "plugins/weather"
    "plugins/power"
    "widgets"
)

add_subdirectory("common")
add_subdirectory("daemon")
add_subdirectory("widgets")
add_subdirectory("plugins")
add_subdirectory("tests")

file(GLOB FRAME_SRCS "frame/*.h" "frame/*.cpp" "frame/*.qrc")
add_executable(aspace ${FRAME_SRCS})
target_link_libraries(aspace PRIVATE
    Qt5::Widgets
    Qt5::UiPlugin
    widgets
    common)

install(TARGETS aspace RUNTIME DESTINATION ${CMAKE_ISNTALL_BINDIR})
install(FILES misc/org.deepin.aspace.gschema.xml DESTINATION ${CMAKE_INSTALL_SCHEMADIR})
install(FILES misc/aspace.service DESTINATION ${CMAKE_INSTALL_SYSTEMDDIR})
install(FILES misc/org.deepin.aspace.desktop DESTINATION ${CMAKE_INSTALL_ENTRYDIR})