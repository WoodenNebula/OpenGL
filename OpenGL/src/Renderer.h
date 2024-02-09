#pragma once
 

#include "VertexArray.h"
#include "Shader.h"
#include "Buffer.h"
#include <GLFW\glfw3.h>

class Renderer
{
private:
	float m_speed;
	GLFWwindow* m_window;
public:
	Renderer(GLFWwindow* Window);
	~Renderer();


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

};