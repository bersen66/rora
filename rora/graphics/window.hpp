#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <string>

#include <rora/graphics/environment.hpp>


namespace graphics
{

class Window
{
public:
	Window(Environment& env, int width, int height, const std::string& title);
	Window(const Window& other) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&& other) = delete;
	~Window();

	operator GLFWwindow* () { return window_; }

	void NewFrameImgui();

	void SwapBuffers();

	void RenderImgui();

	bool ShouldClose();

	void PollEvents();

	void ClearScreen();
private:
	GLFWwindow* ConstructWindow(Environment& env, int width, int height, const std::string& title);

	void InitImguiContext();
	void DestroyImguiContext();

private:
	::std::string title_;
	Environment& env_;
	int width_;
	int height_;
	GLFWwindow* window_;
};

} // namespace graphics

