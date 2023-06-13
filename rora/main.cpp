#include <glad/glad.h>
#include <GLFW/glfw3.h>



#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include <rora/graphics/graphics.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

std::string LoadShaderText(const std::string& path)
{
	std::ifstream in{ path };

	return { std::istreambuf_iterator<char>{ in }, std::istreambuf_iterator<char>{}};
}



int main(int argc, char** argv)
{
	
	try
	{
		graphics::Environment env;
		graphics::Window window(env, /*wd=*/800, /*hg=*/600, /*title=*/"Rora");
		env.SwapInterval(/*interval=*/0);
	 
	 	glViewport(0, 0, 800, 600);
	 
	 	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	 	
	 	float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
	};
	 
	 	unsigned int VBO;
	 	glGenBuffers(1, &VBO);
	 	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	 
	 	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	 	auto vertex_shader_source = LoadShaderText("shaders/vertex.glsl");
	 	const char* vs = vertex_shader_source.c_str();
	 	glShaderSource(vertex_shader, 1, &vs, NULL);
	 	glCompileShader(vertex_shader);
	 
	 	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	 	auto fragment_shader_source = LoadShaderText("shaders/fragment.glsl");
	 
	 	const char* fs = fragment_shader_source.c_str();
	 	glShaderSource(fragment_shader, 1, &fs, NULL);
	 	glCompileShader(fragment_shader);
	 
	 	unsigned int shader_program = glCreateProgram();
	 	glAttachShader(shader_program, vertex_shader);
	 	glAttachShader(shader_program, fragment_shader);
	 	glLinkProgram(shader_program);
	 	glUseProgram(shader_program);
	 
	 	glDeleteShader(vertex_shader); // Нам больше не нужны шейдеры
	 	glDeleteShader(fragment_shader);
	 
	 	unsigned int vao;
	 	glGenVertexArrays(1, &vao);
	 	glBindVertexArray(vao);
	 
	 	glVertexAttribPointer(/*index=*/0,
	 			/*size=*/3,
	 			/*type=*/GL_FLOAT,
	 			/*enable_normalization=*/GL_FALSE,
	 			/*offset=*/sizeof(GL_FLOAT) * 3,
	 			/*pointer?*/(void*)0);
	 
	 	glEnableVertexAttribArray(0);
	 
	 	std::string shader_src = LoadShaderText("vertex.glsl");
	 	printf("%s", shader_src.c_str());
	 
	 
	 	while (!window.ShouldClose())
	 	{
	 		window.PollEvents();
	 		process_input(window);

			window.ClearScreen();
	 
	 		glUseProgram(shader_program);			// logic
	 		glBindVertexArray(vao);					// logic
	 		glDrawArrays(GL_TRIANGLES, 0, 3);		// logic

	 		window.NewFrameImgui();	
			ImGui::Begin("FPS");
				ImGui::Text(std::to_string(ImGui::GetIO().Framerate).c_str());
			ImGui::End();
	 		window.RenderImgui();
	 
	 		window.SwapBuffers();
	 	}
	} 
	catch (const std::exception& exc)
	{
		printf("%s", exc.what());
	}

	return 0;
}