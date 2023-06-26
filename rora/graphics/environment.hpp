#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <rora/graphics/rendering/rendering.hpp>

namespace graphics
{

struct Environment
{
public:
	Environment();
	~Environment();
	Environment(const Environment& other) = delete;
	Environment& operator=(const Environment& other) = delete;
	Environment(Environment&& other) = delete;
	Environment& operator=(Environment&& other) = delete;

	void SwapInterval(int interval);
	void SelectContext(GLFWwindow* window);

	void Plug(const ShaderProgram& program);
	void Plug(const VertexArray& vao);
	
public:
	GLFWmonitor* primary_monitor;
};

} // namespace graphics