#include "stdpch.h"
#include "Shader.h"

#include <GL/glew.h>


Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
	:m_VertexFilePath(vertexFilePath), m_FragmentFilePath(fragmentFilePath),  m_ProgramID(0)
{
	std::string vertexSrc = ParseShader(vertexFilePath);
	std::string fragmentSrc = ParseShader(fragmentFilePath);

	m_ProgramID = CreateShaderProgram(vertexSrc, fragmentSrc);
}

void Shader::Bind() const
{
	glUseProgram(m_ProgramID);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

uint32_t Shader::GetProgramID()
{
	return m_ProgramID;
}


std::string Shader::ParseShader(const char* filePath)
{
	std::fstream shaderFile(filePath);
	std::string line;
	std::stringstream ss;

	//Ensure that shader file is open
	if (!shaderFile.is_open())
	{
		std::cout << "ERROR::SHADER::FILE::READ -> Couldn't open shader file!\n" << filePath << std::endl;
		__debugbreak();
	}

	while (std::getline(shaderFile, line))
	{
		ss << line.c_str() << "\n";
	}

	return ss.str() ;
}

/* creates a shader program that has to be attached and linked */
uint32_t Shader::CreateShaderProgram(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
{
	uint32_t vertexShader, fragmentShader;
	vertexShader = CompileShader(ShaderType::VERTEX, vertexShaderSrc);
	fragmentShader = CompileShader(ShaderType::FRAGMENT, fragmentShaderSrc);


	uint32_t shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	// Error Checking
	int isLinked = 0;

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		int length = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);

		char* infoLog = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(shaderProgram, length, &length, infoLog);

		std::cout << "ERROR::SHADER : LINKING FAILED \n" << infoLog << std::endl;

		glDeleteShader(shaderProgram);

		return 0;
	}

	glValidateProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

uint32_t Shader::CompileShader(ShaderType type, const std::string& shaderSrc)
{
	/// Compilation Process
	uint32_t shaderID = 0;
	const char* src = shaderSrc.c_str();
	if (type == ShaderType::VERTEX)
	{
		shaderID = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == ShaderType::FRAGMENT)
	{
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else
	{
		std::cout << "ERROR::SHADER::BadShaderType" << std::endl;
		__debugbreak();
	}
	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);

	// Error Handling
	int isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	if (!isCompiled)
	{
		int length = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

		char* infoLog = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(shaderID, length, &length, infoLog);

		std::cout << "ERROR::SHADER::" << (type == ShaderType::VERTEX ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n"
			<< infoLog << std::endl;

		glDeleteShader(shaderID);

		return 0;
	}

	return shaderID;
}


void Shader::SetUniform1i(const std::string& name, int value) const
{
	glUniform1i(GetUniformLocation(name), value);
}


void Shader::SetUniform1f(const std::string& name, float value) const
{
	glUniform1f(GetUniformLocation(name), value);
}


void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}


void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) const
{
	// transpose is necessary if matrix is row major
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}


uint32_t Shader::GetUniformLocation(const std::string& name) const
{
	// check if the uniform already exists and if it does, return its location
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_ProgramID, name.c_str());
	if (location == -1)
	{
		std::cout << "SHADER::UNIFORM -> Uniform "<< name <<" Doesn't Exist" << std::endl;
		ASSERT(false);
	}

	m_UniformLocationCache[name] = location;
	return location;
}
