#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Shader.h"
#include "VertexArrayObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


int main()
{
	Renderer::Init(3, 3);
	Window* window = Renderer::CreateWindow(800, 600, "Chess");
	Renderer::SetViewPort(800, 600);

	 float vertices[] = {
		-0.5f, -0.5f,  0.0f,	//0
		 0.5f, -0.5f,  0.0f,	//1
		 0.5f,  0.5f,  0.0f,	//2
		-0.5f,  0.5f,  0.0f,	//3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	
	/// VAO must be bound first
	/// then VBO bind and set data
	/// then EBO/IBO bind and set data
	/// then configure vertex attributes
	
	Shaders shader("./res/shader.shader");

	VertexArrayObject VAO;

	VertexBuffer VBO(vertices, sizeof(vertices));
	IndexBuffer IBO(indices, sizeof(indices));

	VAO.ConfigureVertexAttribPointer(0, 3, 3 * sizeof(float), (void*)0);

	Renderer::LineMode(true);

	while (!Renderer::EndRenderLoop(window))
	{
		/* Render here */
		Renderer::ProcessInput(window);
		Renderer::Draw(VAO, VBO, IBO, shader, window);
	}	
	
	Renderer::Exit(window);
	return 0;
}