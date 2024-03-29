#include "Window.h"

#include <iostream>
#include <string>

#include "glad/glad.h"

Window* Window::Create(const WindowProps& props) { return new Window(props); }

Window::Window(const WindowProps& props) { Init(props); }

Window::~Window() { Shutdown(); }

static std::string glSeverityDecoder(const GLenum& severity) {
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            return "High";
        case GL_DEBUG_SEVERITY_MEDIUM:
            return "Mid";
        case GL_DEBUG_SEVERITY_LOW:
            return "Low";
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            return "Notification";
    }
    return "NONE";
}

static std::string glTypeDecoder(const GLenum& type) {
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            return "ERROR";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return "DEPRECATED_BEHAVIOR";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return "UNDEFINED_BEHAVIOR";
        default:
            return "OTHER";
    }
    return "NONE";
}

/// TODO: IMPLEMENT EVENT HANDLING
void Window::Init(const WindowProps& props) {
    // GLFW Initialization
    {
        // Setting Error callback for GLFW functions
        glfwSetErrorCallback([](int errCode, const char* errMsg) {
            std::cout << "GLFW::[ERROR] - " << errCode << " : " << errMsg
                      << std::endl;
#ifdef _DEBUG
            exit(EXIT_FAILURE);
#endif  // _DEBUG
        });

        if (glfwInit() == GLFW_TRUE) {
            std::cout << "GLFW::[NOTE] - GlFW INITIALIZATION SUCCESSFUL!!!"
                      << std::endl;
        } else {
            std::cout << "GLFW::[ERROR] - GlFW INITIALIZATION FAILED!!!"
                      << std::endl;
            abort();
        }

        /* Explicitly set the opengl version 4.3 (what we are using) */
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
    }  // GLFW Initialization

    // Window Creation
    {
        m_Data.Title = props.Title;
        m_Data.Height = props.Height;
        m_Data.Width = props.Width;

        m_WindowHandle = glfwCreateWindow((int)props.Width, (int)props.Height,
                                          props.Title.c_str(), 0, 0);

        if (m_WindowHandle == NULL) {
            std::cout << "[Error] : line " << __LINE__ << " -> "
                      << "\tWindow Creation Failed" << std::endl;
            glfwTerminate();
        }

        glfwMakeContextCurrent(m_WindowHandle);

        glfwSetWindowUserPointer(m_WindowHandle, &m_Data);
        SetVSync(true);
    }

    // GLAD Initialization
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            // Problem: glewInit failed, something is seriously wrong.
            std::cout << "gladInit failed, aborting." << std::endl;
            glfwTerminate();
        }

        glEnable(GL_DEBUG_OUTPUT);

        // glDebugMessageCallback(
        //     [](GLenum source, GLenum type, GLuint id, GLenum severity,
        //        GLsizei length, const char* message, const void* userParam) {
        //         if (severity < GL_DEBUG_SEVERITY_NOTIFICATION)
        //             std::cout << "GL::[" << glSeverityDecoder(severity) <<
        //             "]"
        //                       << "Type = " << glTypeDecoder(type) << "\n\t->
        //                       "
        //                       << message << std::endl;

        //         if (severity == GL_DEBUG_SEVERITY_HIGH) exit(EXIT_FAILURE);
        //     },
        //     (void*)0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glViewport(0, 0, m_Data.Width, m_Data.Height);
    }  // GLAD Initialization

    // GLFW Callbacks
    {
        glfwSetFramebufferSizeCallback(m_WindowHandle, [](GLFWwindow* window,
                                                          int newWidth,
                                                          int newHeight) {
            glViewport(0, 0, newWidth, newHeight);
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.Height = newHeight;
            data.Width = newWidth;
        });

        glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key,
                                              int scancode, int action,
                                              int mods) {
            // Exit on ESC
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, true);
                std::cout << "ESC pressed, exiting application" << std::endl;
            }

            // Start Rendering on Space
            if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
                extern bool startRendering;
                startRendering = !startRendering;

                if (startRendering)
                    std::cout << "SPACE pressed: STARTING RENDERING"
                              << std::endl;
                else if (!startRendering)
                    std::cout << "SPACE pressed: PAUSING RENDERING"
                              << std::endl;
            }

            if (key == GLFW_KEY_R && action == GLFW_PRESS) {
                extern bool rickAstley;
                if (!rickAstley) {
                    rickAstley = true;
                    std::cout << "Render Next: Rick" << std::endl;
                } else
                    std::cout << "RICK ALREADY ROLLED" << std::endl;
            }

            if (key == GLFW_KEY_F && action == GLFW_PRESS) {
                extern bool rickAstley;
                if (rickAstley) {
                    rickAstley = false;
                    std::cout << "Render Next: NOT Rick" << std::endl;
                } else
                    std::cout << "RICK ALREADY GAVE YOU UP" << std::endl;
            }

            // Fullscreen Windows
            if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
                static bool isFullScrreen = false;
                GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

                static int lastWidth = 0, lastHeight = 0;
                static int lastX = 0, lastY = 0;

                if (!isFullScrreen) {
                    // Saving windowed dimensions for later
                    glfwGetWindowSize(window, &lastWidth, &lastHeight);
                    glfwGetWindowPos(window, &lastX, &lastY);

                    glfwSetWindowMonitor(window, primaryMonitor, NULL, NULL,
                                         1366, 768, 60);
                    std::cout << "F11 PRESSED! CHANGED INTO FULLSCREEN."
                              << std::endl;
                    isFullScrreen = true;
                } else if (isFullScrreen) {
                    glfwSetWindowMonitor(window, nullptr, lastX, lastY,
                                         lastWidth, lastHeight, 60);
                    std::cout << "F11 PRESSED! CHANGED INTO WINDOWED."
                              << std::endl;
                    isFullScrreen = false;
                }
            }
        });

        glfwSetMouseButtonCallback(
            m_WindowHandle,
            [](GLFWwindow* window, int button, int action, int mods) {
                // Mouse Click Collision Check
                if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
                    double cursorX = 0, cursorY = 0;
                    glfwGetCursorPos(window, &cursorX, &cursorY);

                    std::cout << "Mouse Clicked at: (x,y) = (" << cursorX
                              << ", " << cursorY << ")" << std::endl;
                    bool buttonClicked = false;

                    /// Handle CLICKS
                }
            });
    }  // GLFW Callbacks
}

void Window::OnUpdate() {
    /* Poll for events and processes */
    glfwPollEvents();

    /* Swap front and back buffers */
    glfwSwapBuffers(m_WindowHandle);
}

void Window::SetVSync(bool enabled) {
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_Data.VSync = enabled;
}

void Window::Shutdown() {
    glfwDestroyWindow(m_WindowHandle);

    glfwTerminate();
}