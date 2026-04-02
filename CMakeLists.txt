cmake_minimum_required(VERSION 3.25)
project(Vessel)

# Target for root includes (for convenience, not strictly necessary)
add_library(root_includes INTERFACE)
target_include_directories(root_includes INTERFACE ${CMAKE_SOURCE_DIR})

# Order matters, lowest level dependency first
add_subdirectory(Instrumentation)
add_subdirectory(external/glm)
add_subdirectory(external/googletest)
add_subdirectory(Core)
add_subdirectory(Sandbox)
add_subdirectory(TestingApplication)
