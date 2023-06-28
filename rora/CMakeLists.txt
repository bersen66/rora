add_subdirectory(graphics)

add_executable(rora main.cpp application.cpp)

target_link_libraries(
        rora
        glad::glad
        glfw
        graphics
        imgui::imgui
)

add_dependencies(rora copy_resources)