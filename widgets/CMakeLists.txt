# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

project(${WIDGETS}
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "User defined widgets."
    VERSION ${VERSION})

file(GLOB WIDGET_SRCS "*.h" "*.cpp")
add_library(${WIDGETS} SHARED ${WIDGET_SRCS})

target_include_directories(${WIDGETS} PUBLIC
    ${Qt5Widgets_PRIVATE_INCLUDE_DIRS}
    )

target_link_libraries(${WIDGETS} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::UiPlugin
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::Xml
    ${COMMON}
)



install(TARGETS ${WIDGETS} LIBRARY)
