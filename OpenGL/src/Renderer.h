#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ErrorHandler.h"
#include "Shader.h"
#include "VertexArrayObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <string>

#define Window GLFWwindow

namespace Renderer
{

	// Initializes GLFW and sets opengl version and core profile
	void Init(int openGL_Version_Major, int openGL_Version_Minor);

	// Creates and returns a resizeable window* after making it the current context
	GLFWwindow* CreateWindow(int width, int height, const char* windowName);

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


	void Exit(Window* window);
}

// Internal functions
namespace Renderer
{

	// Callback function for resizing windows
	inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}



