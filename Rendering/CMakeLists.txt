cmake_minimum_required(VERSION 3.25)
project(Rendering)

add_library(Rendering INTERFACE)

target_compile_features(Rendering INTERFACE cxx_std_20)

target_include_directories(Rendering INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Rendering INTERFACE root_includes)


