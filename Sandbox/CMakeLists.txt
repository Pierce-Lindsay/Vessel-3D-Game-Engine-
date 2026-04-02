cmake_minimum_required(VERSION 3.25)
project(Sandbox)

# add all source files in Sandbox folder
file(GLOB_RECURSE DIR_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(Sandbox ${DIR_SOURCES})

#publically include all .h files in Sandbox
target_include_directories(Sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Sandbox PRIVATE root_includes)

target_link_libraries(Sandbox PRIVATE Core)