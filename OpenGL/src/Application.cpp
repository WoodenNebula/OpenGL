#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"


int main()
{

	Renderer::Init(3, 3);
	unsigned int width = 800, height = 600;
	Window* window = Renderer::CreateWindow(width, height, "Window");


	Renderer::SetViewPort(800, 600);
	//position, ...
	float vertices[] = {
		//-1.0f,  1.0f,  0.0f,	//
		-1.0f, -1.0f,  0.0f,	//0
		-1.0f, -0.75f,  0.0f,	//1

		-0.75f, -1.0f,  0.0f,	//2
		-0.75f,  -0.75f,  0.0f,	//3

		-0.5f,  -1.0f,  0.0f,	//4
		-0.5f,  -0.75f,  0.0f,	//5
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3,
		2, 3, 4,
		3, 4, 5
	};

	{
		/// VAO must be bound first
		/// then VBO bind and set data
		/// then EBO/IBO bind and set data
		/// then configure vertex attributes

		Shaders shader("./res/shader.shader");

		VertexArrayObject VAO;

		VertexBuffer VBO(vertices, sizeof(vertices));
		IndexBuffer IBO(indices, sizeof(indices));

		VAO.ConfigureVertexAttribPointer(0, 3, 3 * sizeof(float), (void*)0);

		//Renderer::LineMode(false);

		while (!Renderer::EndRenderLoop(window))
		{
			/* Render here */
			Renderer::ProcessInput(window);
			Renderer::Draw(VAO, VBO, IBO, shader, window);
		}


	}
	Renderer::Exit();

	return 0;
}