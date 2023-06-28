#pragma once

#include <rora/graphics/graphics.hpp>

class Application
{
public:
	Application(int argc, char** argv);
	void Run();
private:
	int argc_;
	char** argv_;
};