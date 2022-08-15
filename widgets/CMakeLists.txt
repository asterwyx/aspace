# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

project(${ASPACE_WIDGETS}
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "User defined widgets."
    VERSION ${VERSION})

file(GLOB WIDGET_SRCS "*.h" "*.cpp")
add_library(${ASPACE_WIDGETS} SHARED ${WIDGET_SRCS})

# only find necessary package in its own project scope
find_package(Qt5 REQUIRED COMPONENTS Xml)

target_link_libraries(${ASPACE_WIDGETS} PRIVATE
    Qt::Widgets
    Qt::UiPlugin
    Qt::Svg
    Qt::Xml
)

install(TARGETS ${ASPACE_WIDGETS} LIBRARY)
