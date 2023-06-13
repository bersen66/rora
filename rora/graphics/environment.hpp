#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace graphics
{



struct Environment
{
	friend class Window;
	Environment();
	~Environment();
	Environment(const Environment& other) = delete;
	Environment& operator=(const Environment& other) = delete;
	Environment(Environment&& other) = delete;
	Environment& operator=(Environment&& other) = delete;

	void SwapInterval(int interval);
	void SelectContext(GLFWwindow* window);
};

} // namespace graphics