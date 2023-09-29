#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
	Renderer renderer;
	renderer.Init(4, 3);
	uint32_t width = 800, height = 600;
	renderer.CreateWindow(width, height, "Window");


	renderer.SetViewPort(800, 600);

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


		renderer.LineMode(false);

		shader.Bind();
		// Render Loop
		// -------------------
		while (!renderer.EndRenderLoop())
		{
			float time = glfwGetTime();
			/* Render here */
			float red = (sin(time) + 1 )/ 2;

			shader.SetUniform4F("iColor", red, sin(red), cos(red), 1.0f);

			renderer.ProcessInput();
			renderer.Draw(VA, IBO, shader);
		}


	}
	renderer.Exit();

	return 0;
}