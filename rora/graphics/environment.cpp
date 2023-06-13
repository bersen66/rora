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


