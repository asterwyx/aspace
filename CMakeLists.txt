cmake_minimum_required(VERSION 3.7)

if (NOT DEFINED VERSION)
    set(VERSION "1.0.0")
endif()

project(aspace
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "A space for weather and rest."
    VERSION ${VERSION})

include(GNUInstallDirs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fPIC -Wall -Wextra")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -Wl,--as-needed")

# find qt related package
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui UiPlugin LinguistTools Svg)
set(TS_FILES translations/dde-space_zh_CN.ts)
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

# export include directories and link directories for gtest use
include_directories(
    "interfaces"
    "widgets"
    )
link_directories(
    "plugins/echoeditor"
    "plugins/weather"
    "plugins/power"
    "widgets"
)

file(GLOB FRAME_SRCS "frame/*.h" "frame/*.cpp" "frame/*.qrc")
add_executable(aspace ${FRAME_SRCS})
target_link_libraries(aspace PRIVATE
    Qt5::Widgets
    Qt5::UiPlugin
    widgets
    )

add_subdirectory("daemon")
add_subdirectory("widgets")
add_subdirectory("plugins")
add_subdirectory("tests")
