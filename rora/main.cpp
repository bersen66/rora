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

		std::vector<float> vv = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		} ;

		VertexBuffer VBO;
		glBindBuffer(GL_ARRAY_BUFFER, VBO.Descriptor());
		VBO.InsertData(vv);

		graphics::ShaderProgram pg = graphics::PrepareProgram("shaders/vertex.glsl",
															  "shaders/fragment.glsl");
		

	 	glUseProgram(pg.Descriptor());


		VertexArray VAO;
		glBindVertexArray(VAO.Descriptor());
		VAO.ApplyAttributeLayout(
			AttributeLayout{}
				.SetLocationIndex(0)
				.SetAttribType(GL_FLOAT)
				.SetBufferOffset(0)
				.NeedNormalization(GL_FALSE)
				.SetStride(sizeof(GL_FLOAT) * 3)
				.SetAttributesNumber(3)
		);
		glEnableVertexAttribArray(0);

		glBindVertexArray(VAO.Descriptor());	// logic
	 	glUseProgram(pg.Descriptor());			// logic
	 	

	 	while (!window.ShouldClose())
	 	{
	 		window.PollEvents();
	 		process_input(window);

			window.ClearScreen();
	 

	 		glDrawArrays(GL_TRIANGLES, 0, 3);		// logic

	 		window.NewFrameImgui();	
			ImGui::Begin("FPS");
				ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
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