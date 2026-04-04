cmake_minimum_required(VERSION 3.25)
project(OpenGLImpl)

# add all source files in OpenGLImpl folder
file(GLOB_RECURSE DIR_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(OpenGLImpl STATIC ${DIR_SOURCES})

target_compile_features(OpenGLImpl PUBLIC cxx_std_20)

target_include_directories(OpenGLImpl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(OpenGLImpl PRIVATE Instrumentation)
target_link_libraries(OpenGLImpl PRIVATE Rendering)
target_link_libraries(OpenGLImpl PRIVATE GLFW)
target_link_libraries(OpenGLImpl PRIVATE Glad)
target_link_libraries(OpenGLImpl PRIVATE STB)
target_link_libraries(OpenGLImpl PRIVATE root_includes)