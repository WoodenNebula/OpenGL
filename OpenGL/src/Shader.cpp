#pragma once

#include "Shader.h"

#include <iostream>

Shaders::Shaders() :m_ProgramID(0) {};

Shaders::Shaders(const char* shaderPath)
{
	auto [vertexShaderSrcCode, fragmentShaderSrcCode] = m_ParseShader(shaderPath);
	m_ProgramID = m_CreateShaderProgram(vertexShaderSrcCode.c_str(), fragmentShaderSrcCode.c_str());
}

void Shaders::UseShaderProgram()
{
	GLCall(glUseProgram(m_ProgramID));
}

unsigned int Shaders::GetProgramID()
{
	return m_ProgramID;
}


ShaderSources Shaders::m_ParseShader(const char* filePath)
{
	std::fstream shaderFile(filePath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	//Ensure that shader file is open
	if (!shaderFile.is_open())
	{
		std::cout << "ERROR::SHADER::FILE::READ -> Couldn't open shader file!" << std::endl;
		__debugbreak();
	}

	while (std::getline(shaderFile, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;

		}
		else
		{
			ss[(int)type] << line.c_str() << "\n";
		}
	}

	return { ss[(int)ShaderType::VERTEX].str(), ss[(int)ShaderType::FRAGMENT].str() };
}

/* creates a shader program that has to be attached and linked */
unsigned int Shaders::m_CreateShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc)
{
	unsigned int vertexShader, fragmentShader;
	vertexShader = m_CompileShader(ShaderType::VERTEX, vertexShaderSrc);
	fragmentShader = m_CompileShader(ShaderType::FRAGMENT, fragmentShaderSrc);


	GLCall(unsigned int shaderProgram = glCreateProgram());

	GLCall(glAttachShader(shaderProgram, vertexShader));
	GLCall(glAttachShader(shaderProgram, fragmentShader));
	GLCall(glLinkProgram(shaderProgram));



	GLCall(glValidateProgram(shaderProgram));

	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));

	return shaderProgram;
}

unsigned int Shaders::m_CompileShader(ShaderType type, const char* shaderSrc)
{
	unsigned int shader;
	if (type == ShaderType::VERTEX)
	{
		GLCall(shader = glCreateShader(GL_VERTEX_SHADER));
	}
	else if (type == ShaderType::FRAGMENT)
	{
		GLCall(shader = glCreateShader(GL_FRAGMENT_SHADER));
	}
	else
	{
		std::cout << "ERROR::SHADER::BadShaderType" << std::endl;
		__debugbreak();
	}
	GLCall(glShaderSource(shader, 1, &shaderSrc, NULL));
	GLCall(glCompileShader(shader));

	int success;
	char infoLog[512];
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));

	if (!success)
	{
		GLCall(glGetShaderInfoLog(shader, 512, NULL, infoLog));
		std::cout << "ERROR::SHADER::" << (type == ShaderType::VERTEX ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n"
			<< infoLog << std::endl;
	}

	return shader;
}
