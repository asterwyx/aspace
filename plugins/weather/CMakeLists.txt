set(PLUGIN_NAME "weather")

project(${PLUGIN_NAME})
aux_source_directory("." WEATHER_SRCS)

add_library(weather SHARED ${WEATHER_SRCS})
target_link_libraries(weather PRIVATE Qt5::Widgets)