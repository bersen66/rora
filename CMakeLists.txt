cmake_minimum_required(VERSION 3.25)
project(rora)

set(CMAKE_CXX_STANDARD 20)

include(cmake/copy_resources.cmake)
include(cmake/setup_glad.cmake)
include(cmake/setup_glfw.cmake)
include(cmake/setup_imgui.cmake)
include(cmake/setup_glm.cmake)

set(RESOURCES_DIR resources/)

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(rora)

