#include "stdpch.h"

#include "Window.h"


Window* Window::Create(const WindowProps& props)
{
	return new Window(props);
}


Window::Window(const WindowProps& props)
{
	Init(props);
}


Window::~Window()
{
	Shutdown();
}

/// TODO: IMPLEMENT EVENT HANDLING
void Window::Init(const WindowProps& props)
{
	m_Data.Title = props.Title;
	m_Data.Height = props.Height;
	m_Data.Width = props.Width;

	int success = glfwInit();
	if (!success)
	{
		ASSERT(success);
	}
	

	/* Explicitly set the opengl version 4.3 (what we are using) */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	/* Explicitly set the opengl profile to core (what we are using) */
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_DEBUG_CONTEXT);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const char* Title = props.Title.c_str();
    int Width = (int)props.Width;
    int Height = (int)props.Height;
	m_Window = glfwCreateWindow(Width, Height, Title, NULL, NULL);

	if (m_Window == NULL)
	{
		std::cout << "[Error] : line " << __LINE__ << " -> " << "\tWindow Creation Failed" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(true);

	glViewport(0, 0, m_Data.Width, m_Data.Height);


	// GLFW callbacks
    glfwSetErrorCallback([](int errCode, const char* errMsg)
        {
            std::cout << "[ERROR] " << errCode << ": " << errMsg << std::endl;
            __debugbreak();
        });

	glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int newWidth, int newHeight)
		{
			glViewport(0, 0, newWidth, newHeight);
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.Height = newHeight;
			data.Width = newWidth;
		});


	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
            // Exit on ESC
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            {
                glfwSetWindowShouldClose(window, true);
                std::cout << "ESC pressed, exiting application" << std::endl;
            }


            // Start Rendering on Space
            if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
            {
                extern bool startRendering;
                startRendering = !startRendering;

                if (startRendering)
                    std::cout << "SPACE pressed: STARTING RENDERING" << std::endl;
                else if (!startRendering)
                    std::cout << "SPACE pressed: PAUSING RENDERING" << std::endl;
            }


            if (key == GLFW_KEY_R && action == GLFW_PRESS)
            {
                extern bool rickAstley;
                if (!rickAstley)
                {
                    rickAstley = true;
                    std::cout << "Render Next: Rick" << std::endl;
                }
                else std::cout << "RICK ALREADY ROLLED" << std::endl;
            }


            if (key == GLFW_KEY_F && action == GLFW_PRESS)
            {
                extern bool rickAstley;
                if (rickAstley)
                {
                    rickAstley = false;
                    std::cout << "Render Next: NOT Rick" << std::endl;
                }
                else std::cout << "RICK ALREADY GAVE YOU UP" << std::endl;
            }


            // Fullscreen Windows
            if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
            {
                static bool isFullScrreen = false;
                GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

                static int lastWidth = 0, lastHeight = 0;
                static int lastX = 0, lastY = 0;


                if (!isFullScrreen)
                {
                    //Saving windowed dimensions for later
                    glfwGetWindowSize(window, &lastWidth, &lastHeight);
                    glfwGetWindowPos(window, &lastX, &lastY);

                    glfwSetWindowMonitor(window, primaryMonitor, NULL, NULL, 1366, 768, 60);
                    std::cout << "F11 PRESSED! CHANGED INTO FULLSCREEN." << std::endl;
                    isFullScrreen = true;
                }
                else if (isFullScrreen)
                {

                    glfwSetWindowMonitor(window, nullptr, lastX, lastY, lastWidth, lastHeight, 60);
                    std::cout << "F11 PRESSED! CHANGED INTO WINDOWED." << std::endl;
                    isFullScrreen = false;
                }

            }

		});


    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            // Mouse Click Collision Check
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            {
                double cursorX = 0, cursorY = 0;
                glfwGetCursorPos(window, &cursorX, &cursorY);

                std::cout << "Mouse Clicked at: (x,y) = (" << cursorX << ", " << cursorY << ")" << std::endl;
                bool buttonClicked = false;
                
                ///Handle CLICKS

            }
        });


}


void Window::OnUpdate()
{
	/* Poll for events and processes */
	glfwPollEvents();

	/* Swap front and back buffers */
	glfwSwapBuffers(m_Window);
}

void Window::SetVSync(bool enabled)
{
	if(enabled)
		glfwSwapInterval(1);
	else 
		glfwSwapInterval(0);

	m_Data.VSync = enabled;
}


void Window::Shutdown()
{
	glfwDestroyWindow(m_Window);
}