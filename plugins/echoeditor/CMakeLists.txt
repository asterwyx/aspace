set(PLUGIN_NAME "echo-editor")

project(${PLUGIN_NAME})

aux_source_directory("." ECHO_EDITOR_SRCS)

add_library(echoeditor SHARED ${ECHO_EDITOR_SRCS})
target_link_libraries(echoeditor PRIVATE Qt5::Widgets)
