aux_source_directory("." SERVER_SRCS)

link_directories(
    "../widgets"
    )

add_executable(dde-space ${SERVER_SRCS})
target_link_libraries(dde-space PRIVATE
    Qt5::Widgets
    Qt5::UiPlugin
    widgets
    )
