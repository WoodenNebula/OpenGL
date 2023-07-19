#pragma once
#ifndef RENDERER
#define RENDERER

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VertexArrayObject.h"
#include "Buffer.h"

#include <iostream>
#include <string>

#define Window GLFWwindow

namespace Renderer
{
	// Initializes GLFW and sets opengl version and core profile
	void Init(int openGL_Version_Major, int openGL_Version_Minor);

	// Creates a resizeable window on the Window* provided after making it the current context and initializing glew as well
	Window* CreateWindow(int width, int height, const char* windowName);

	// Sets OpenGL view port while performing errorchecks
	void SetViewPort(int width, int height);

	void ProcessInput(Window* window);

	// Returns true if window is closed and the render loop is to be stopped
	bool EndRenderLoop(Window* window);

	// Hint OpenGl to draw only the borders
	void LineMode(bool drawInLineMode);

	/// <summary>
	/// Binds the VAO, VBO, IBO, uses shaderprogram and finally renders the vertices as triangles
	/// </summary>
	/// <param name="VAO">: Vertex Array Object</param>
	/// <param name="VBO">: Vertex Buffer Object</param>
	/// <param name="IBO">: Elemnt/Index Buffer Object</param>
	/// <param name="shader">: Shader Object</param>
	/// <param name="window">: Window object to render to</param>
	void Draw(VertexArrayObject& VAO, VertexBuffer& VBO, IndexBuffer& IBO, Shaders& shader, Window* window);


	void Exit();
}

// Internal functions
namespace Renderer
{
	// Initialize GLEW after having a valid window context
	inline void InitGlew()
	{
		/* Initializing GLEW library */
		if (glewInit() != GLEW_OK)
		{
			std::cout << "[Error] : GLEW initialization failed!" << std::endl;
			abort();
		}
	}

	// Callback function for resizing windows
	inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}


#endif // !RENDERER