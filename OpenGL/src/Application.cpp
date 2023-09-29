#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Callbacks.h"
#include "Renderer.h"

void initGLFW(uint32_t openGL_Version_Major, uint32_t openGL_Version_Minor)
{
	glfwSetErrorCallback(glfw_error_callback);

	if (!glfwInit())
	{
		/* Explicitly set the opengl version 3.3 (what we are using) */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGL_Version_Major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGL_Version_Minor);

		/* Explicitly set the opengl profile to core (what we are using) */
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_DEBUG_CONTEXT);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	return;
}

//struct Coord2D
//{
//	float x;
//	float y;
//};
//
//class Quad
//{
//public:
//	Coord2D center;
//	float vertices[];
//
//
//};



int main()
{
	initGLFW(4, 3);

	Renderer renderer;
	
	uint32_t width = 800, height = 600;
	renderer.CreateWindow(width, height, "Window");
	renderer.SetViewPort(800, 600);

	float vertices[] = {
		// positions        
		 0.0f,  1.0f,	// 0 top mid
		-0.5f,  0.0f,	// 1 mid left
		 0.5f,  0.0f	// 2 mid right
	};

	uint32_t indices[] = {
		0, 1, 2
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

		layout.Push<float>(2);	//pos
		VA.AddBuffer(VBO, layout);

		shader.Bind();
		// Render Loop
		// -------------------
		while (!renderer.EndRenderLoop())
		{
			float time = glfwGetTime();

			shader.SetUniform4F("offset", sin(time)/2 , cos(time), 0.0f, 1.0f);

			renderer.Draw(VA, IBO, shader);
			renderer.ProcessInput();
		}


	}
	renderer.Exit();

	return 0;
}