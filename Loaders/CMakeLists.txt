cmake_minimum_required(VERSION 3.25)
project(Loaders)

# add all source files in Loaders folder
file(GLOB_RECURSE DIR_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(Loaders STATIC ${DIR_SOURCES})

target_compile_features(Loaders PUBLIC cxx_std_23)  

target_include_directories(Loaders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Loaders PRIVATE Instrumentation)

target_link_libraries(Loaders PRIVATE Rendering)

target_link_libraries(Loaders PRIVATE root_includes)