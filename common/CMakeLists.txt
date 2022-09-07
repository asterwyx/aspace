# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

project(${COMMON}
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "Common data manipulation"
    VERSION ${VERSION})

file(GLOB COMMON_SRCS "*.h" "*.cpp")
add_library(${COMMON} SHARED ${COMMON_SRCS})

target_link_libraries(${COMMON} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::DBus
)

install(TARGETS ${COMMON} LIBRARY)
install()