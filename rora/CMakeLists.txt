add_subdirectory(graphics)

add_executable(rora main.cpp)

target_link_libraries(
        rora
        glad::glad
        glfw
        graphics
        imgui::imgui
)