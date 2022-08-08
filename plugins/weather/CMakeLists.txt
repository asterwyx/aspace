set(PLUGIN_NAME "weather")

project(${PLUGIN_NAME})
file(GLOB WEATHER_SRCS "*.h" "*.cpp")

add_library(weather SHARED ${WEATHER_SRCS})
target_link_libraries(weather PRIVATE Qt5::Widgets)
