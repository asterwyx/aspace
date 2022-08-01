aux_source_directory("src" SERVER_SRCS)

include_directories("include")
include_directories("../interfaces")

add_executable(dde-space ${SERVER_SRCS})
target_link_libraries(dde-space PRIVATE Qt5::Widgets)
