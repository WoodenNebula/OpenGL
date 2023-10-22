#pragma once
#ifndef RENDERER
#define RENDERER

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "Shader.h"
#include "Buffer.h"
#include "Assert.h"

#include <string>


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
	GLFWwindow* m_window;
	float m_speed;
public:
	Renderer();
	~Renderer();

	void InitGLFW(uint32_t openGL_Version_Major, uint32_t openGL_Version_Minor) const;

	GLFWwindow* GetWindow() const;

	// Sets OpenGL view port while performing errorchecks
	void SetViewPort(int width, int height);

	void SetSpeed(float speed);

	void ProcessInput();

	// Returns true if window is closed and the render loop is to be stopped
	bool EndRenderLoop();

	// Hint OpenGl to draw only the borders
	void LineMode(bool drawInLineMode);

	void ClearScreen();

	void SetBackGroundColor(const glm::vec3& Color);

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
};

#endif // !RENDERER