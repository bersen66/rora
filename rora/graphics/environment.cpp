#include <rora/graphics/environment.hpp>

#include <stdexcept>

namespace graphics
{

Environment::Environment()
{
	if (!glfwInit())
	{
		throw std::runtime_error{"Environment creation failed"};
	}
	primary_monitor = glfwGetPrimaryMonitor();
	if (primary_monitor == NULL) 
	{
		throw std::runtime_error("Monitor not created");
	}
}

Environment::~Environment()
{
	glfwTerminate();
}

void Environment::SwapInterval(int interval)
{
	glfwSwapInterval(interval);
}


void Environment::SelectContext(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Glad not loaded!");
	}
}

} // namespace graphics


