#pragma once
#ifndef ERROR_HANDLER
#define ERROR_HANDLER

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearErrors();\
	x;\
	ASSERT(GLLogCall(#x, __LINE__, __FILE__))

/* Reset all the error flags previously raised/unattended */
void GLClearErrors();

/* Converts the GLenum error codes into string error messages */
const std::string GLEnumErrorDecoder(GLenum error);

/* Logs the error details */
bool GLLogCall(const char* functionName, int line, const char* file);


#endif // !ERROR_HANDLER