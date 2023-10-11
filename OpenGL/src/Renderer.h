#pragma once
#ifndef RENDERER
#define RENDERER

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Callbacks.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Buffer.h"

#include <iostream>
#include <string>

#define Window GLFWwindow

struct WindowHint
{
	uint32_t width;
	uint32_t height;
	std::string title;

	uint32_t viewWidth;
	uint32_t viewHeight;

};

class Renderer
{
private:
	Window* m_window;
public:
	Renderer();
	~Renderer();

	void InitGLFW(uint32_t openGL_Version_Major, uint32_t openGL_Version_Minor) const;

	Window* GetWindow() const;

	// Sets OpenGL view port while performing errorchecks
	void SetViewPort(int width, int height);

	void ProcessInput();

	// Returns true if window is closed and the render loop is to be stopped
	bool EndRenderLoop();

	// Hint OpenGl to draw only the borders
	void LineMode(bool drawInLineMode);

	void ClearScreen();

	/// <summary>
	/// Binds the VA, IBO, uses shaderprogram and finally renders the vertices as triangles
	/// </summary>
	/// <param name="VA">: Vertex Array Object</param>
	/// <param name="IBO">: Elemnt/Index Buffer Object</param>
	/// <param name="shader">: Shader Object</param>
	void Draw(const VertexArray& VA, const IndexBuffer& IBO, const Shader& shader);


	void Exit();

public:
	// Creates a resizeable window on the Window* provided after making it the current context and initializing glew as well
	void CreateWindow(WindowHint winHint);


private:
	// Initialize GLEW after having a valid window context
	void InitGlew()
	{
		/* Initializing GLEW library */
		if (glewInit() != GLEW_OK)
		{
			std::cout << "[Error] : GLEW initialization failed!" << std::endl;
			return;
		}
	}

	
};

#endif // !RENDERER