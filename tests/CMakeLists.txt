# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

project(ut-${CLIENT}
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "A space for weather and rest."
    VERSION ${VERSION})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

find_package(GTest REQUIRED)

file(GLOB_RECURSE TEST_SRCS "frame/*.cpp" "*.cpp")

add_executable(${PROJECT_NAME}
    ${TEST_SRCS}
    ../frame/mainwindow.cpp
    ../frame/pluginloader.cpp
    ../frame/res.qrc
    )
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::DBus
    Qt${QT_VERSION_MAJOR}::Network
    GTest::gtest
    GTest::gmock
    ${QGSettings_LIBRARIES}
    ${WIDGETS}
    ${COMMON}
    gcov
    dl
    ${CLIENT}-weather
    )

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-instr-generate -ftest-coverage)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
endif ()

target_compile_options(${PROJECT_NAME} PRIVATE -fno-access-control)

