cmake_minimum_required(VERSION 3.25)
project(STB)

# add all source files in STB folder
file(GLOB_RECURSE DIR_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(STB STATIC ${DIR_SOURCES})

target_include_directories(STB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})