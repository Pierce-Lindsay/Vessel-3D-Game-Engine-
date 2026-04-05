cmake_minimum_required(VERSION 3.25)
# Set the runtime library to MultiThreadedDLL for both Debug and Release configurations
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL" CACHE STRING "" FORCE)
project(Vessel)

# Target for root includes (for convenience, not strictly necessary)
add_library(root_includes INTERFACE)
target_include_directories(root_includes INTERFACE ${CMAKE_SOURCE_DIR})

# Order matters, lowest level dependency first
add_subdirectory(external/glm)
add_subdirectory(external/googletest)
add_subdirectory(external/Glad)
add_subdirectory(external/STB)
add_subdirectory(external/GLFW)

add_subdirectory(Instrumentation)
add_subdirectory(Context)
add_subdirectory(Rendering)

add_subdirectory(renderingAPI/OpenGLImpl)

add_subdirectory(Core)
add_subdirectory(Sandbox)
add_subdirectory(TestingApplication)
