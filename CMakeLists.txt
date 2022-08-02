cmake_minimum_required(VERSION 3.7)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(dde-space VERSION 1.0 LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "-g -Wall")

include(GNUInstallDirs)

file(GLOB INTERFACES "interface/*.h")

find_package(Qt5 REQUIRED COMPONENTS Widgets Gui LinguistTools)
set(TS_FILES translations/dde-space_zh_CN.ts)
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

include_directories("interfaces")

add_subdirectory("server")
add_subdirectory("plugins")
add_subdirectory("tests")
