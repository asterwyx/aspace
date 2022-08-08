project(widgets
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/asterwyx/aspace
    DESCRIPTION "User defined widgets."
    VERSION ${VERSION})

file(GLOB SRCS "*.h" "*.cpp")
add_library(widgets SHARED ${SRCS})

# only find necessary package in its own project scope
find_package(Qt5 REQUIRED COMPONENTS Xml)

target_link_libraries(widgets PRIVATE
    Qt::Widgets
    Qt::UiPlugin
    Qt::Svg
    Qt::Xml
)
