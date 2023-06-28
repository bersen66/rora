#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <cstddef>
#include <stdio.h>
#include <exception>

#include <rora/application.hpp>

int main(int argc, char** argv)
{
	try
	{
		Application app(argc, argv);
		app.Run();
	} 
	catch (const std::exception& exc)
	{
		printf("%s", exc.what());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}