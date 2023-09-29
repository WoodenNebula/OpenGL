#pragma once

#include "Renderer.h"

#include <iostream>
#include <sstream>
#include <string>

 Window* Renderer::GetWindow() const 
{
	ASSERT(m_window != nullptr);
	return m_window;
};


 void Renderer::CreateWindow(int width, int height, const char* windowName)
{
	m_window = glfwCreateWindow(width, height, windowName, NULL, NULL);
	if (m_window == nullptr)
	{
		std::cout << "[Error] : line " << __LINE__ << " -> " << "\n\tWindow Creation Failed" << std::endl;
		glfwTerminate();
	}
	else
	{
		glfwMakeContextCurrent(m_window);

		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

		InitGlew();

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(opengl_error_callback, 0);
	}
}


void Renderer::SetViewPort(int width, int height)
{
	/* Setting the size of the viewable area */
	
	glViewport(0, 0, width, height);
}

void Renderer::ProcessInput()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_window, true);
	}
}

bool Renderer::EndRenderLoop()
{
	return glfwWindowShouldClose(m_window);
}

void Renderer::LineMode(bool drawInLineMode)
{
	if (drawInLineMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else return;
}

void Renderer::Draw(const VertexArray& VA, const IndexBuffer& IBO, const Shader& shader)
{
	/* Color of background of window */
	glClearColor(0.6f, 0.693f, 0.69f, 1.0f);

	/* Clean and assign new color to back buffer*/
	glClear(GL_COLOR_BUFFER_BIT);


	shader.Bind();
	VA.Bind();
	IBO.Bind();

//TODO: CONFIGURE DEEZ
	///
	/// Primitive(shape) we want to use
	/// How many indices we want to draw
	/// Data type of indices
	/// Index of indices 
	/// 
	glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, 0);

	/* Swap front and back buffers */
	glfwSwapBuffers(m_window);

	/* Poll for events and processes */
	glfwPollEvents();
}

void Renderer::Exit()
{
	glfwTerminate();
}

