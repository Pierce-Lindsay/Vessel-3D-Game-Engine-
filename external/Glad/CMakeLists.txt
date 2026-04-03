cmake_minimum_required(VERSION 3.25)
project(Glad)

# add all source files in Glad folder
file(GLOB_RECURSE DIR_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_library(Glad STATIC ${DIR_SOURCES})

target_include_directories(Glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})