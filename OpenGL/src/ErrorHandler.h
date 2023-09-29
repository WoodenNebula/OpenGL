#pragma once
#ifndef ERROR_HANDLER
#define ERROR_HANDLER

#include <GL\glew.h>
#include <GLFW\glfw3.h>


#define ASSERT(x) if(!(x)) __debugbreak()



#endif // !ERROR_HANDLER