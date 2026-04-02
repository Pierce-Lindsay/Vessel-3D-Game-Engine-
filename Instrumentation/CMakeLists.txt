cmake_minimum_required(VERSION 3.25)
project(Instrumentation)

# add all source files in Instrumentation folder
file(GLOB_RECURSE DIR_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(Instrumentation STATIC ${DIR_SOURCES})

target_compile_features(Instrumentation PUBLIC cxx_std_20)  

target_include_directories(Instrumentation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Instrumentation PRIVATE root_includes)
