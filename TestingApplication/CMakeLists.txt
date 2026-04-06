cmake_minimum_required(VERSION 3.25)
project(TestingApplication)

# add all source files in TestingApplication folder
file(GLOB_RECURSE DIR_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(TestingApplication ${DIR_SOURCES})

#publically include all .h files in TestingApplication
target_include_directories(TestingApplication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TestingApplication PRIVATE root_includes)

target_link_libraries(TestingApplication PRIVATE Core)
target_link_libraries(TestingApplication PRIVATE gtest)
target_link_libraries(TestingApplication PRIVATE gtest_main)