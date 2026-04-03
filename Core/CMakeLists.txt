cmake_minimum_required(VERSION 3.25)
project(Core)

# add all source files in Core folder
file(GLOB_RECURSE CORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(Core STATIC ${CORE_SOURCES})

target_compile_features(Core PUBLIC cxx_std_20)  

#publically include all .h files in Core
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Core PRIVATE root_includes)

target_link_libraries(Core PUBLIC Instrumentation)

target_link_libraries(Core PUBLIC glm)

target_link_libraries(Core PRIVATE Rendering)