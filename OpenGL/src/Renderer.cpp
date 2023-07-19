#pragma once

#include "Renderer.h"

#include <iostream>
#include <sstream>
#include <string>

void Renderer::Init(int openGL_Version_Major, int openGL_Version_Minor)
{

	/* Initializing GLFW library */
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "[Error] : line " << __LINE__ << " from (" << "glfwInit" << ")"
			<< " -> " << GLFW_FALSE << "\n\tFailed to initialize glfw" << " : " << __FILE__ << std::endl;
	}

	/* Explicitly set the opengl version 3.3 (what we are using) */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGL_Version_Major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGL_Version_Minor);

	/* Explicitly set the opengl profile to core (what we are using) */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

Window* Renderer::CreateWindow(int width, int height, const char* windowName)
{
	Window* window = glfwCreateWindow(width, height, windowName, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "[Error] : line " << __LINE__ << " -> " << NULL << "\n\tWindow Creation Failed" << std::endl;
		glfwTerminate();
		return 0;
	}
	else
	{
		glfwMakeContextCurrent(window);

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		InitGlew();
	}
	return window;
}


void Renderer::SetViewPort(int width, int height)
{
	/* Setting the size of the viewable area */
	GLCall(glViewport(0, 0, width, height));
}

void Renderer::ProcessInput(Window* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

bool Renderer::EndRenderLoop(Window* window)
{
	return glfwWindowShouldClose(window);
}

void Renderer::LineMode(bool drawInLineMode)
{
	if (drawInLineMode)
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
}

void Renderer::Draw(VertexArrayObject& VAO, VertexBuffer& VBO, IndexBuffer& IBO, Shaders& shader, Window* window)
{
	/* Color of background of window */
	GLCall(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));

	/* Clean and assign new color to back buffer*/
	GLCall(glClear(GL_COLOR_BUFFER_BIT));


	shader.UseShaderProgram();
	VAO.Bind();

//TODO: CONFIGURE DEEZ
	///
	/// Primitive(shape) we want to use
	/// How many indices we want to draw
	/// Data type of indices
	/// Index of indices 
	/// 
	GLCall(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0));

	/* Swap front and back buffers */
	GLCall(glfwSwapBuffers(window));

	/* Poll for events and processes */
	GLCall(glfwPollEvents());
}

void Renderer::Exit()
{
	glfwTerminate();
}

