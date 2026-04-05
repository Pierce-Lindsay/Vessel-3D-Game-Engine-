cmake_minimum_required(VERSION 3.25)
project(Rendering)

# add all source files in Rendering folder
file(GLOB_RECURSE DIR_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(Rendering STATIC ${DIR_SOURCES})

target_compile_features(Rendering PRIVATE cxx_std_20)

target_include_directories(Rendering PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Rendering PRIVATE root_includes)


