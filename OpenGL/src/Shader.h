#pragma once

#include "ErrorHandler.h"

#include <fstream>
#include <sstream>

enum class ShaderType
{
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

struct ShaderSources
{
	std::string VertexSource;
	std::string fragmentSource;
};

class Shaders
{
public:
	Shaders();
	Shaders(const char* shaderPath);
	unsigned int GetProgramID();

	void UseShaderProgram();

private:
	ShaderSources m_ParseShader(const char* filePath);
	unsigned int m_CreateShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc);
	unsigned int m_CompileShader(ShaderType type, const char* shaderSrc);

private:
	unsigned int m_ProgramID;
};

