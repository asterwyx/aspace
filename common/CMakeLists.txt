# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

project(${ASPACE_COMMON}
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "Common data manipulation"
    VERSION ${VERSION})

file(GLOB COMMON_SRCS "*.h" "*.cpp")
add_library(${ASPACE_COMMON} SHARED ${COMMON_SRCS})

target_link_libraries(${ASPACE_COMMON} PRIVATE
    Qt::Widgets
    Qt::DBus
)

install(TARGETS ${ASPACE_COMMON} LIBRARY)
install()