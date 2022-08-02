aux_source_directory("src" SERVER_SRCS)
aux_source_directory("." SERVER_SRCS)

include_directories("include")

add_executable(dde-space ${SERVER_SRCS})
target_link_libraries(dde-space PRIVATE Qt5::Widgets)
