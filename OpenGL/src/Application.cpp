#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <iostream>
#include <string>


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

	
	//Generate a Vertex Array Object for opengl to use
	///
	/// VAO must be bound first
	/// then VBO bind and set data
	/// then EBO/IBO bind and set data
	/// then configure vertex attributes
	/// 
	unsigned int VAO;
	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glBindVertexArray(VAO));

	Shaders shader("./res/shader.shader");

	VertexBuffer VBO(vertices, sizeof(vertices));
	IndexBuffer IBO(indices, sizeof(indices));


	unsigned int attribIndex = 0;
	unsigned int vertexElementCount = 3;
	unsigned int strideSize = 3 * sizeof(float);
	void* attribOffset = 0;
	//Setting memory layout of array buffers(vb) in GPU
//TODO: CONFIGURE DEEZ
	///
	/// position of Vertex Attribute (position, texture coord, color, etc)
	/// No. of value per vertex
	/// Type of vertex data
	/// need to normalize?
	/// stride size (data between each attribute)
	/// offset of the vertex attrib within the vertex (if vertex has 3d position and color, then the offset for color will be different)
	/// 
	GLCall(glVertexAttribPointer(attribIndex, vertexElementCount, GL_FLOAT, GL_FALSE, strideSize, attribOffset));
	GLCall(glEnableVertexAttribArray(0));

	// Draws only the border
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	
	while (!Renderer::EndRenderLoop(window))
	{
		/* Render here */
		Renderer::ProcessInput(window);
		Renderer::Draw(VAO, VBO, IBO, shader, window);
	}	
	
	Renderer::Exit(window);
	return 0;
}


