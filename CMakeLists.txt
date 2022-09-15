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

set(CLIENT  "${PROJECT_NAME}")
set(COMMON  "${CLIENT}-common")      # For linker use
set(WIDGETS "${CLIENT}-widgets")    # Specify library name in advance so it can be used in all subprojects
SET(DAEMON  "${CLIENT}-daemon")

if (NOT DEFINED DBUS_SERVICE_NAME)
set(DBUS_SERVICE_NAME "org.deepin.aspace")
endif()
if (NOT DEFINED PLUGIN_DIR)
set(PLUGIN_DIR "${CMAKE_INSTALL_PREFIX}/lib/aspace/plugins")
endif()
if(NOT DEFINED SCHEMA_ID)
    set(SCHEMA_ID "org.deepin.aspace")
endif()
if(NOT DEFINED SCHEMA_PATH)
    set(SCHEMA_PATH "/org/deepin/aspace/")
endif()
add_compile_definitions(
    DBUS_SERVICE_NAME="${DBUS_SERVICE_NAME}"
    PLUGIN_DIR="${PLUGIN_DIR}"
    SCHEMA_ID="${SCHEMA_ID}"
    SCHEMA_PATH="${SCHEMA_PATH}"
)

include(GNUInstallDirs)
set(CMAKE_INSTALL_LIBDIR "lib/aspace")
set(CMAKE_INSTALL_SCHEMADIR "share/glib-2.0/schemas")
set(CMAKE_INSTALL_DBUSDIR "share/dbus-1/services")
set(CMAKE_INSTALL_SYSTEMDDIR "lib/systemd/user")
set(CMAKE_INSTALL_ENTRYDIR "share/applications")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# for qt auto moc and auto rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# common flags and platform independent flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--as-needed")

if (CMAKE_INSTALL_PREFIX_SET_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

# default we have a debug build
if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "debug")
endif()
string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)
if (CMAKE_BUILD_TYPE STREQUAL "debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fsanitize=address -fno-omit-frame-pointer")
    set(BUILD_TEST ON)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
endif ()

# find qt related package
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Gui UiPlugin LinguistTools Svg DBus Network Concurrent Xml)
find_package(PkgConfig REQUIRED)
pkg_search_module(QGSettings REQUIRED gsettings-qt)
find_package(DtkWidget REQUIRED)
find_package(DtkCMake REQUIRED)

# create qt files
set(TS_FILES translations/aspace_zh_CN.ts)
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

# export include directories and link directories for easy use
include_directories(
    "interfaces"
    "common"
    "daemon"
    "frame"
    "plugins/weather"
    "widgets"
    ${QGSettings_INCLUDE_DIRS}
    ${DtkWidget_INCLUDE_DIRS}
)

link_directories(
    "common"
    "daemon"
    "frame"
    "plugins/weather"
    "widgets"
)

add_subdirectory("common")
add_subdirectory("widgets")
add_subdirectory("daemon")
add_subdirectory("plugins")
if(BUILD_TEST)
    enable_testing()
    # Only build test when needed
    add_subdirectory("tests")
endif()

file(GLOB_RECURSE FRAME_SRCS "frame/*.h" "frame/*.cpp" "frame/assets/*.qrc")
add_executable(${CLIENT}
    ${FRAME_SRCS}
    )

target_link_libraries(${CLIENT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::UiPlugin
    Qt${QT_VERSION_MAJOR}::DBus
    Qt${QT_VERSION_MAJOR}::Concurrent
    Qt${QT_VERSION_MAJOR}::Xml
    ${QGSettings_LIBRARIES}
    ${DtkWidget_LIBRARIES}
    ${WIDGETS}
    ${COMMON}
    )

install(TARGETS ${CLIENT} RUNTIME)
set(CLIENT_BIN "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}/${CLIENT}")
configure_file(misc/org.deepin.aspace.desktop.in "${DBUS_SERVICE_NAME}.desktop")
install(FILES "${PROJECT_BINARY_DIR}/org.deepin.aspace.desktop" DESTINATION ${CMAKE_INSTALL_ENTRYDIR})
dconfig_meta_files(APPID org.deepin.aspace FILES misc/org.deepin.aspace.json)
install(FILES misc/org.deepin.aspace.gschema.xml DESTINATION ${CMAKE_INSTALL_SCHEMADIR})
set(DAEMON_BIN "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}/${DAEMON}")
configure_file(misc/org.deepin.aspace.service.in "${DBUS_SERVICE_NAME}.service")
install(FILES "${PROJECT_BINARY_DIR}/${DBUS_SERVICE_NAME}.service" DESTINATION ${CMAKE_INSTALL_DBUSDIR})
configure_file(misc/aspace.service.in "${CLIENT}.service")
install(FILES "${PROJECT_BINARY_DIR}/${CLIENT}.service" DESTINATION ${CMAKE_INSTALL_SYSTEMDDIR})
configure_file(misc/update-weather.timer.in update-weather.timer)
install(FILES "${PROJECT_BINARY_DIR}/update-weather.timer" DESTINATION ${CMAKE_INSTALL_SYSTEMDDIR})


add_custom_target(uninstall COMMENT "Uninstall installed files")
add_custom_command(
    TARGET uninstall
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo "Nothing in install_manifest.txt to be uninstalled!"
)
add_custom_target(make_ln ALL COMMENT "Make soft links for libraries.")
add_custom_command(
    TARGET make_ln
    POST_BUILD
    COMMENT "Make soft links for libraries in advance"
    COMMAND ln -sf ../aspace/lib${WIDGETS}.so lib${WIDGETS}.so
    COMMAND ln -sf ../aspace/lib${COMMON}.so lib${COMMON}.so
)

install(FILES ${PROJECT_BINARY_DIR}/lib${WIDGETS}.so ${PROJECT_BINARY_DIR}/lib${COMMON}.so DESTINATION lib/x86_64-linux-gnu)
install(SCRIPT post_install.cmake)
