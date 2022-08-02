set(PLUGIN_NAME "dde-weather")

project(${PLUGIN_NAME})
aux_source_directory("." WEATHER_SRCS)

add_library(dde-weather SHARED ${WEATHER_SRCS})
target_link_libraries(dde-weather PRIVATE Qt5::Widgets)