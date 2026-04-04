cmake_minimum_required(VERSION 3.25)
project(Context)

# add all source files in Context folder
file(GLOB_RECURSE DIR_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(Context STATIC ${DIR_SOURCES})

target_compile_features(Context PUBLIC cxx_std_20)

target_include_directories(Context PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Context PRIVATE Instrumentation)
target_link_libraries(Context PRIVATE GLFW)
target_link_libraries(Context PRIVATE root_includes)
