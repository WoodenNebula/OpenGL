#pragma once
#ifndef SHADER
#define SHADER

#include "Assert.h"
#include "glm/glm.hpp"

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
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const char* shaderPath);
	uint32_t GetProgramID();

	void Bind() const;
	void UnBind() const;

	// Uniforms
	void SetUniform1i(const std::string& name, int v0) const;
	void SetUniform1f(const std::string& name, float value) const;
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) const;

	uint32_t GetUniformLocation(const std::string& name) const;
private:
	ShaderSources ParseShader(const char* filePath);
	uint32_t CreateShaderProgram(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
	uint32_t CompileShader(ShaderType type, const std::string& shaderSrc);
};

#endif // !SHADER