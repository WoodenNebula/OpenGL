#include "stdpch.h"

#include "Renderer.h"
#include "Callbacks.h"

Renderer::Renderer() :m_window(nullptr), m_speed(0.75f) {}


Renderer::~Renderer() {}


void Renderer::InitGLFW(unsigned int openGL_Version_Major, unsigned int openGL_Version_Minor) const
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
}


GLFWwindow* Renderer::GetWindow() const
{
	ASSERT(m_window != nullptr);
	return m_window;
};


 void Renderer::CreateWindow(WindowHint winHint)
{
	m_window = glfwCreateWindow(winHint.width, winHint.height, winHint.title.c_str(), NULL, NULL);
	if (m_window == nullptr)
	{
		std::cout << "[Error] : line " << __LINE__ << " -> " << "\n\tWindow Creation Failed" << std::endl;
		glfwTerminate();
	}
	else
	{
		glfwMakeContextCurrent(m_window);

		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

		glfwSetKeyCallback(m_window, glfw_key_callback);

		glfwSetMouseButtonCallback(m_window, glfw_mouse_button_callback);

		/* Initializing GLEW library */
		if (glewInit() != GLEW_OK)
		{
			std::cout << "[Error] : GLEW initialization failed!" << std::endl;
			return;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(opengl_error_callback, 0);
	}
}


void Renderer::SetViewPort(int width, int height)
{
	/* Setting the size of the viewable area */
	glViewport(0, 0, width, height);
}

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