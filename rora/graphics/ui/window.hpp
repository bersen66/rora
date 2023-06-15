#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <string>

#include <rora/graphics/environment.hpp>

#include <glm/vec4.hpp>


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

	operator GLFWwindow* ();

	void NewFrameImgui();

	void SwapBuffers();

	void RenderImgui();

	bool ShouldClose();

	void PollEvents();

	void ClearScreen();

	void BackgroundColor(const ::glm::vec4& color);

	void SetFullScreenMode(bool flag);

	bool InFullScreenMode() const;

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
	::glm::vec4 bg_color_;
	bool in_fullscreen_;
};

} // namespace graphics

