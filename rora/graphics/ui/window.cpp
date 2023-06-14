#include <rora/graphics/ui/window.hpp>
#include <stdexcept>
#include <cstdio>


namespace graphics
{

Window::Window(Environment& env, int width, int height, const std::string& title)
	: title_(title)
	, env_(env)
	, width_(width)
	, height_(height)
	, window_(ConstructWindow(env, width, height, title))
{
	env.SelectContext(*this);
	InitImguiContext();
}


Window::~Window()
{
	DestroyImguiContext();
	glfwDestroyWindow(window_);
}


void Window::InitImguiContext()
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window_, true);
	ImGui_ImplOpenGL3_Init();
}

void Window::DestroyImguiContext()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Window::NewFrameImgui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

Window::operator GLFWwindow* ()
{
	return window_;
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(window_);
}

void Window::RenderImgui()
{
	ImGui::Render();										 
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());	 
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(window_);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::ClearScreen()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);		 
}

GLFWwindow* Window::ConstructWindow(Environment& env, int width, int height, const std::string& title)
{
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* result = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (result == nullptr)
	{
		throw std::runtime_error("Window not created!\n");
	}

	return result;

}

} // namespace graphics
