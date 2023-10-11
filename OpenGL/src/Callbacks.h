#pragma once
#include <GLFW/glfw3.h>

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

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        std::cout << "ESC pressed, exiting application" << std::endl;
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        extern bool startRendering;
        startRendering = !startRendering;

        if(startRendering)
            std::cout << "SPACE pressed: STARTING RENDERING" << std::endl;
        else if(!startRendering)
            std::cout << "SPACE pressed: PAUSING RENDERING" << std::endl;

    }


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