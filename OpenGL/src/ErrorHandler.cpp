#include "ErrorHandler.h"

#include <iostream>
#include <string>


void GLClearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}


const std::string GLEnumErrorDecoder(GLenum error)
{
	if (error == GL_INVALID_ENUM)
		return std::string("GL_INVALID_ENUM");
	else if (error == GL_INVALID_VALUE)
		return std::string("GL_INVALID_VALUE");
	else if (error == GL_INVALID_OPERATION)
		return std::string("GL_INVALID_OPERATION");
	else if (error == GL_INVALID_FRAMEBUFFER_OPERATION)
		return std::string("GL_INVALID_FRAMEBUFFER_OPERATION");
	else if (error == GL_OUT_OF_MEMORY)
		return std::string("GL_OUT_OF_MEMORY");
	else return std::string("UNKNOWN ERROR");
}

bool GLLogCall(const char* functionName, int line, const char* file)
{
	while (GLenum errorCode = glGetError())
	{
		std::cout << "[Error] : " << line << " from " << functionName << " -> "
			<< errorCode << " \n\t" << GLEnumErrorDecoder(errorCode) << " : " << file << std::endl;
		return false;
	}
	return true;
}