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

set(CLIENT_NAME "aspace")

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

# platform independent flags and debug flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fPIC -Wall -Wextra")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--as-needed")

# find qt related package
find_package(PkgConfig REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui UiPlugin LinguistTools Svg DBus Network)
pkg_search_module(QGSettings REQUIRED gsettings-qt)

# create qt files
set(TS_FILES translations/aspace_zh_CN.ts)
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

# export include directories and link directories for gtest use
include_directories(
    "interfaces"
    "widgets"
    "common"
)
link_directories(
    "plugins/weather"
    "widgets"
)

set(ASPACE_COMMON "aspace-common") # For linker use
add_subdirectory("common")
set(ASPACE_WIDGETS "aspace-widgets")
add_subdirectory("widgets")
add_subdirectory("daemon")
add_subdirectory("plugins")
add_subdirectory("tests")

file(GLOB FRAME_SRCS "frame/*.h" "frame/*.cpp" "frame/*.qrc")
add_executable(${CLIENT_NAME} ${FRAME_SRCS})
target_include_directories(${CLIENT_NAME} PRIVATE
    ${QGSettings_INCLUDE_DIRS}
    )
target_link_libraries(${CLIENT_NAME} PRIVATE
    Qt5::Widgets
    Qt5::UiPlugin
    Qt5::DBus
    ${QGSettings_LIBRARIES}
    ${ASPACE_WIDGETS}
    ${ASPACE_COMMON}
    )

install(TARGETS ${CLIENT_NAME} RUNTIME)
set(CLIENT_BIN "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}/${CLIENT_NAME}")
configure_file(misc/org.deepin.aspace.desktop.in "${DBUS_SERVICE_NAME}.desktop")
install(FILES "${PROJECT_BINARY_DIR}/org.deepin.aspace.desktop" DESTINATION ${CMAKE_INSTALL_ENTRYDIR})

install(FILES misc/org.deepin.aspace.gschema.xml DESTINATION ${CMAKE_INSTALL_SCHEMADIR})

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
    COMMAND ln -sf ../aspace/lib${ASPACE_WIDGETS}.so lib${ASPACE_WIDGETS}.so
    COMMAND ln -sf ../aspace/lib${ASPACE_COMMON}.so lib${ASPACE_COMMON}.so
)

install(FILES ${PROJECT_BINARY_DIR}/lib${ASPACE_WIDGETS}.so ${PROJECT_BINARY_DIR}/lib${ASPACE_COMMON}.so DESTINATION lib/x86_64-linux-gnu)
install(SCRIPT post_install.cmake)
