set(PLUGIN_NAME "echo-editor")

project(${PLUGIN_NAME})

aux_source_directory("." ECHO_EDITOR_SRCS)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_library(echoeditor SHARED ${ECHO_EDITOR_SRCS})
target_link_directories(echoeditor PRIVATE Qt5::Widgets)