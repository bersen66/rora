#include <rora/application.hpp>


Application::Application(int argc, char** argv)
	: argc_(argc)
	, argv_(argv)
{

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(graphics::Window& window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		window.SetFullScreenMode(!window.InFullScreenMode());
	}
}

void Application::Run()
{
	graphics::Environment env;
	graphics::Window window(env, /*wd=*/800, /*hg=*/600, /*title=*/"Rora");
	window.SetFullScreenMode(false);
	env.SwapInterval(/*interval=*/0);


	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	std::vector<float> vv = {
		// positions           // colors
		 0.5f,   0.5f,  0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		 0.5f,   -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 -0.5f,  -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // top 
		 -0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 1.0f,   // top 
	};

	std::vector<unsigned int> indicies =
	{
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	graphics::VertexArrayBuilder vab;
	vab.AddVertexAttribute<float>(3);
	vab.AddVertexAttribute<float>(3);

	graphics::VertexArray vao = vab.Build();
	vao.LoadVertexBufferData(vv.data(), sizeof(float) * vv.size());
	vao.LoadIndexBufferData(indicies.data(), sizeof(unsigned int) * indicies.size());

	graphics::ShaderProgram pg = graphics::PrepareProgram("resources/shaders/vertex.glsl",
		"resources/shaders/fragment.glsl");

	env.Plug(pg);
	env.Plug(vao);

	while (!window.ShouldClose())
	{
		window.PollEvents();
		ProcessInput(window);

		window.ClearScreen();


		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window.NewFrameImgui();
		ImGui::Begin("FPS");
			ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		ImGui::End();
		window.RenderImgui();

		window.SwapBuffers();
	}

}