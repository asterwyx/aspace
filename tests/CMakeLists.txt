cmake_minimum_required(VERSION 3.7)

find_package(GTest REQUIRED)

aux_source_directory("." TEST_SRCS)

add_executable(dde-space-unit-test ${TEST_SRCS})

target_link_libraries(dde-space-unit-test PRIVATE GTest::GTest)
