#pragma once
#include <GLFW/glfw3.h>
#include "Quad2D.h"

#include <iostream>


static void glfw_error_callback(int errCode, const char* errMsg)
{
	std::cout << "[ERROR] " << errCode << ": " << errMsg << std::endl;
	__debugbreak();
}


static const char* glSeverityDecoder(const GLenum& severity)
{
    switch (severity)
    {
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

static const char* glTypeDecoder(const GLenum& type)
{
    switch (type)
    {
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

static void GLAPIENTRY opengl_error_callback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    std::cout << "[GL CALLBACK: " << glSeverityDecoder(severity) << "]" << "Type = " << glTypeDecoder(type) <<
        "\n\t-> " << message << std::endl;


    if (severity == GL_DEBUG_SEVERITY_HIGH)
        __debugbreak();
}

// Callback function for resizing windows
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


// Callback for SINGLE keypress event
static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
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

        if(startRendering)
            std::cout << "SPACE pressed: STARTING RENDERING" << std::endl;
        else if(!startRendering)
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
}


// Callback for mouse button event
static void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    // Mouse Click Collision Check
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double cursorX = 0, cursorY = 0;
        glfwGetCursorPos(window, &cursorX, &cursorY);

        std::cout << "Mouse Clicked at: (x,y) = (" << cursorX << ", " << cursorY << ")" << std::endl;
        bool buttonClicked = false;

        extern std::vector<std::unique_ptr<Quad2D>> quadList;

        bool click = false;
        for (const auto& quad : quadList)
        {
            click = quad->ClickCollision(cursorX, cursorY);
            if (click)
            {
                std::cout << "Collision Successful! BUTTON PRESSED" << std::endl;
                // Handle Successful collision
            }
            else
            {
                // Handle Unsuccessful collision
            }
        }

    }
}
