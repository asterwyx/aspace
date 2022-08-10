# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

project(common
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "Common data manipulation"
    VERSION ${VERSION})

file(GLOB COMMON_SRCS "*.h" "*.cpp")
add_library(common SHARED ${COMMON_SRCS})

target_link_libraries(common PRIVATE
    Qt::Widgets
    Qt::DBus
)