#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{

	Renderer::Init(3, 3);
	uint32_t width = 800, height = 600;
	Window* window = Renderer::CreateWindow(width, height, "Window");


	Renderer::SetViewPort(800, 600);
	// Texture - Black [0.0f, 0.5f)
	// Texture - White [0.5f, 0.5f]

	float vertices[] = {
		// positions          // colors           // texture coords
		-0.5f,  0.5f, 0.0f,		// top left 
		 0.5f,  0.5f, 0.0f,		// top right
		 0.5f, -0.5f, 0.0f,		// bottom right
		-0.5f, -0.5f, 0.0f		// bottom left
	};

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	{
		 /*Normal Pipeline of the program
		 VA must be bound first
		 then VBO bind and set data
		 then EBO/IBO bind and set data
		 then configure vertex attributes*/

		Shader shader("./res/shader/shader.shader");

		VertexArray VA;
		VertexBuffer VBO(vertices, sizeof(vertices));
		IndexBuffer IBO(indices, sizeof(indices));
		VertexBufferLayout layout;

		layout.Push<float>(3);
		VA.AddBuffer(VBO, layout);


		Renderer::LineMode(false);

		shader.Bind();
		// Render Loop
		// -------------------
		while (!Renderer::EndRenderLoop(window))
		{
			float time = glfwGetTime();
			/* Render here */
			float red = (sin(time) + 1 )/ 2;

			shader.SetUniform4F("iColor", red, sin(red), cos(red), 1.0f);


			Renderer::ProcessInput(window);
			Renderer::Draw(VA, IBO, shader, window);
		}


	}
	Renderer::Exit();

	return 0;
}