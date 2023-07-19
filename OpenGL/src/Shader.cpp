#pragma once

#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const char* shaderPath)
	:m_FilePath(shaderPath), m_ProgramID(0)
{
	ShaderSources source = ParseShader(shaderPath);
	m_ProgramID = CreateShaderProgram(source.VertexSrc, source.FragmentSrc);
}

void Shader::UseShaderProgram()
{
	GLCall(glUseProgram(m_ProgramID));
}

unsigned int Shader::GetProgramID()
{
	return m_ProgramID;
}


ShaderSources Shader::ParseShader(const char* filePath)
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
unsigned int Shader::CreateShaderProgram(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
{
	unsigned int vertexShader, fragmentShader;
	vertexShader = CompileShader(ShaderType::VERTEX, vertexShaderSrc.c_str());
	fragmentShader = CompileShader(ShaderType::FRAGMENT, fragmentShaderSrc.c_str());


	GLCall(unsigned int shaderProgram = glCreateProgram());

	GLCall(glAttachShader(shaderProgram, vertexShader));
	GLCall(glAttachShader(shaderProgram, fragmentShader));
	GLCall(glLinkProgram(shaderProgram));



	GLCall(glValidateProgram(shaderProgram));

	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));

	return shaderProgram;
}

unsigned int Shader::CompileShader(ShaderType type, const std::string& shaderSrc)
{
	/// Compilation Process
	unsigned int shaderID;
	const char* src = shaderSrc.c_str();
	if (type == ShaderType::VERTEX)
	{
		GLCall(shaderID = glCreateShader(GL_VERTEX_SHADER));
	}
	else if (type == ShaderType::FRAGMENT)
	{
		GLCall(shaderID = glCreateShader(GL_FRAGMENT_SHADER));
	}
	else
	{
		std::cout << "ERROR::SHADER::BadShaderType" << std::endl;
		__debugbreak();
	}
	GLCall(glShaderSource(shaderID, 1, &src, nullptr));
	GLCall(glCompileShader(shaderID));

	// Error Handling
	int success;
	GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		int length;
		GLCall(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length));

		char* infoLog = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(shaderID, length, &length, infoLog));

		std::cout << "ERROR::SHADER::" << (type == ShaderType::VERTEX ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n"
			<< infoLog << std::endl;

		return 0;
	}

	return shaderID;
}

void Shader::SetUniform4F(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
	// check if the uniform already exists and if it does, return its location
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_ProgramID, name.c_str()));
	if (location == -1)
		std::cout << "SHADER::UNIFORM -> Uniform "<< name <<" Doesn't Exist" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}
