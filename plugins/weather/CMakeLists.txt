# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

set(PLUGIN_NAME "aspace-weather")

project(${PLUGIN_NAME})
file(GLOB WEATHER_SRCS "*.h" "*.cpp" "assets/*.qrc" "models/*.h" "models/*.cpp" "controllers/*.h" "controllers/*.cpp" "views/*.h" "views/*.cpp")
add_library(${PLUGIN_NAME} SHARED ${WEATHER_SRCS})
target_link_libraries(${PLUGIN_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::DBus
    Qt${QT_VERSION_MAJOR}::Concurrent
    ${WIDGETS}
    ${COMMON}
)
install(TARGETS ${PLUGIN_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_PLUGINDIR})
