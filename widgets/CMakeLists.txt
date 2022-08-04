project(widgets
    LANGUAGES CXX
    VERSION 1.0.0
)

file(GLOB SRCS "*.h" "*.cpp")
add_library(widgets SHARED ${SRCS})
target_link_libraries(widgets PRIVATE Qt::Widgets Qt::UiPlugin)