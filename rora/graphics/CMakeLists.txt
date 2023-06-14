add_library(
	graphics

	ui/window.cpp
	ui/window.hpp
	graphics.hpp
	environment.cpp
	environment.hpp

	rendering/buffers/vbo.h
    rendering/buffers/vao.h
    rendering/buffers/attribute_layout.h
    rendering/buffers/ibo.h
	rendering/bytes.h

	rendering/buffers/vbo.cpp
    rendering/buffers/attribute_layout.cpp
    rendering/buffers/vao.cpp
    rendering/buffers/ibo.cpp

	rendering/shaders/shader.h
	rendering/shaders/shader.cpp
)

target_link_libraries(
	graphics
	glad::glad
    glfw
)