 

#include "Renderer.h"


Renderer::Renderer(GLFWwindow* Window) :m_window(Window), m_speed(0.75f) {}


Renderer::~Renderer() {}



void Renderer::SetSpeed(float speed)
{
	m_speed = speed;
}



/// <summary>
/// Handle inputs from each frame
/// </summary>
void Renderer::ProcessInput()
{
	if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		extern float xOffset;
		int currWidth = 0, currHeight = 0;
		glfwGetWindowSize(m_window, &currWidth, &currHeight);
		//if(xOffset <= currWidth)
		xOffset = xOffset - m_speed;
	}

	if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		extern float xOffset;
		int currWidth = 0, currHeight = 0;
		glfwGetWindowSize(m_window, &currWidth, &currHeight);

		xOffset = xOffset + m_speed;
	}

	if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		extern float yOffset;
		int currWidth = 0, currHeight = 0;
		glfwGetWindowSize(m_window, &currWidth, &currHeight);
		//if (yOffset <= currHeight)
		yOffset = yOffset + m_speed;
	}

	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		extern float yOffset;
		int currWidth = 0, currHeight = 0;
		glfwGetWindowSize(m_window, &currWidth, &currHeight);
		//if (yOffset <= currHeight)
		yOffset = yOffset - m_speed;
	}
}


bool Renderer::EndRenderLoop()
{
	return glfwWindowShouldClose(m_window);
}


void Renderer::LineMode(bool drawInLineMode = false)
{
	if (drawInLineMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}


void Renderer::ClearScreen()
{
	/* Clean and assign new color to back buffer*/
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SetBackGroundColor(const glm::vec3& Color)
{
	glClearColor(Color.r, Color.g, Color.b, 1.0f);
}


void Renderer::Draw(const VertexArray& VA, const IndexBuffer& IBO, const Shader& shader)
{
	/* Color of background of window */
	glClearColor(0.2f, 0.39f, 0.32f, 1.0f);

	shader.Bind();
	VA.Bind();
	IBO.Bind();

	///
	/// Primitive(shape) we want to use
	/// How many indices we want to draw
	/// Data type of indices
	/// Index of indices 
	///
	glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, 0);
}


void Renderer::Exit()
{
	glfwTerminate();
}