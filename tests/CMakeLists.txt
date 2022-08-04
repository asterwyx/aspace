cmake_minimum_required(VERSION 3.7)

find_package(GTest REQUIRED COMPONENTS GTest Main)

aux_source_directory("." TEST_SRCS)

link_directories(
    "../plugins/echoeditor"
    "../plugins/weather"
    "../plugins/power"
    "../widgets"
)

add_executable(dde-space-unit-test ${TEST_SRCS})

target_link_libraries(dde-space-unit-test PRIVATE
    Qt::Widgets
    Qt::UiPlugin
    GTest::GTest
    GTest::Main
    widgets
    )
