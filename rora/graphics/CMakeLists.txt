add_library(
	graphics
	window.cpp
	window.hpp
	graphics.hpp
	environment.cpp
	environment.hpp
)

target_link_libraries(
	graphics
	glad::glad
    glfw
)