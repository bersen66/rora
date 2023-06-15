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
	, bg_color_(/*r=*/0.2f, /*g=*/0.3f, /*b=*/0.3f, /*a=*/1.0f)
	, in_fullscreen_(false)
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
	glClearColor(bg_color_.r, bg_color_.g, bg_color_.b, bg_color_.a);
	glClear(GL_COLOR_BUFFER_BIT);		 
}

void Window::BackgroundColor(const ::glm::vec4& color)
{
	bg_color_ = color;
}

void Window::SetFullScreenMode(bool flag)
{
	if (flag == in_fullscreen_)
	{
		return;
	}

	if (flag == true)
	{
		GLFWmonitor* monitor = env_.primary_monitor;
		const GLFWvidmode* vm = glfwGetVideoMode(monitor);
		if (vm == nullptr)
		{
			throw std::runtime_error("Can't get videomode");
		}
		glfwSetWindowMonitor(window_, monitor, /*xpos*/0, /*ypos*/0, vm->width, vm->height, vm->refreshRate);
	}
	else
	{
		glfwSetWindowMonitor(window_, nullptr, 200, 200, width_, height_, GLFW_DONT_CARE);
	}
	in_fullscreen_ = flag;
}

bool Window::InFullScreenMode() const
{
	return in_fullscreen_;
}

GLFWwindow* Window::ConstructWindow(Environment& env, int width, int height, const std::string& title)
{
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* result = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (result == nullptr)
	{
		throw std::runtime_error("Window not created!\n");
	}

	return result;

}

} // namespace graphics
