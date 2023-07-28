#pragma once
#ifndef SHADER
#define SHADER

#include "ErrorHandler.h"

#include <string>
#include <unordered_map>


enum class ShaderType
{
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

struct ShaderSources
{
	std::string VertexSrc;
	std::string FragmentSrc;
};

class Shader
{
private:
	uint32_t m_ProgramID;
	const std::string m_FilePath;
	std::unordered_map<std::string, uint32_t> m_UniformLocationCache;

public:
	Shader(const char* shaderPath);
	uint32_t GetProgramID();

	void UseShaderProgram();

	// Set uniform data for 4 floats
	void SetUniform4F(const std::string& name, float v0, float v1, float v2, float v3);

	uint32_t GetUniformLocation(const std::string& name);
private:
	ShaderSources ParseShader(const char* filePath);
	uint32_t CreateShaderProgram(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
	uint32_t CompileShader(ShaderType type, const std::string& shaderSrc);
};

#endif // !SHADER