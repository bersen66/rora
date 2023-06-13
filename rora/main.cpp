#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

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

	int glfw_initiated = glfwInit();
	if (glfw_initiated != GLFW_TRUE)
	{
		printf("GLFW initialization failed");
		return -1;
	}

	printf("GLFW initialized\n");

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

	GLFWwindow* window = glfwCreateWindow(1920, 1040, "OpenGL tutorial", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return -1;
	}

	
	ImGui::CreateContext();
	
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();


	printf("glad initialized\n");

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


	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		process_input(window);


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/////////////////////////////////////////////////
		ImGui::Begin("FPS");
			ImGui::Text(std::to_string(ImGui::GetIO().Framerate).c_str());
		ImGui::End();
		/////////////////////////////////////////////////


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(shader_program);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);


	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}