# SPDX-FileCopyrightText: 2022 Astrea Wang
#
# SPDX-License-Identifier: GPL-3.0-or-later

project(ut-${CLIENT}
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "A space for weather and rest."
    VERSION ${VERSION})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

file(GLOB_RECURSE TEST_SRCS "daemon/*.cpp" "frame/*.cpp" "*.cpp" "stubs/*.cpp" "common/*.cpp" "weather/*.cpp")
file(GLOB_RECURSE WIDGET_SRCS "../widgets/*.cpp")
file(GLOB_RECURSE COMMON_SRCS "../common/*.cpp")
file(GLOB_RECURSE WEATHER_SRCS "../plugins/weather/assets/res.qrc" "../plugins/weather/controllers/*.cpp" "../plugins/weather/models/*.cpp" "../plugins/weather/views/*.cpp" "../plugins/weather/*.cpp")

add_executable(${PROJECT_NAME}
    ${TEST_SRCS}
    ${WIDGET_SRCS}
    ${COMMON_SRCS}
    ${WEATHER_SRCS}
    ../frame/mainwindow.cpp
    ../frame/pages/page.cpp
    ../frame/pages/selectingpage.cpp
    ../frame/pages/contentpage.cpp
    ../frame/pages/loadingpage.cpp
    ../frame/pluginloader.cpp
    ../frame/assets/res.qrc
    ../daemon/aspace.cpp
    ../daemon/weatherservice.cpp
    )


target_include_directories(${PROJECT_NAME} PRIVATE "stubs")

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::DBus
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::UiPlugin
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Concurrent
    ${QGSettings_LIBRARIES}
    ${DtkWidget_LIBRARIES}
    gtest
    gmock
    gcov
    pthread
    )
target_include_directories(${PROJECT_NAME} PUBLIC
    ${Qt5Widgets_PRIVATE_INCLUDE_DIRS}
    )

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-instr-generate -ftest-coverage)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
endif ()

target_compile_options(${PROJECT_NAME} PRIVATE -fno-access-control)

