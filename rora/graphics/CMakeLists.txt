add_library(
	graphics

	ui/window.cpp
	ui/window.hpp
	graphics.hpp

	environment.cpp
	environment.hpp

	rendering/shader.hpp
	rendering/shader.cpp
	rendering/details/casts.hpp
	rendering/details/bytes.hpp
	
    rendering/vertex_array.cpp
	rendering/vertex_array.hpp
)

target_link_libraries(
	graphics
	glad::glad
    glfw
	glm::glm
)