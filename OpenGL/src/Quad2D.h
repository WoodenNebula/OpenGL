#pragma once

#include "stdpch.h"

#include "glm/glm.hpp"

struct Coord2D
{
	float x;
	float y;
};

struct WindowHint
{
	uint32_t width;
	uint32_t height;
	std::string title;

	uint32_t viewWidth;
	uint32_t viewHeight;

};

class Shader;
class VertexArray;
class VertexBuffer;
class IndexBuffer;
class VertexBufferLayout;
class Texture;

class Quad2D
{
private:
	Coord2D m_Center;
	float m_width, m_height;

	float m_vertices[16];
	unsigned int m_indices[6];

	std::vector<glm::vec3> m_initialPosition;

	std::unique_ptr<Shader> m_QuadShader;
	std::unique_ptr<VertexArray> m_VA;
	std::unique_ptr<VertexBuffer> m_VB;
	std::unique_ptr<IndexBuffer> m_IB;
	std::unique_ptr<VertexBufferLayout> m_Layout;
	std::unique_ptr<Texture> m_Texture;
	WindowHint m_Dimensions;

public:

	/// <summary>
	/// Generates a Quad in 2D space at the specified position with diameter scaled by given scalar
	/// </summary>
	/// <param name="center">Position at screen space(pixel) at which the quad will have its center</param>
	/// <param name="scale"></param>
	Quad2D(const WindowHint& dimensions, const Coord2D& center, float width, float height, const std::string& texturePath);


	~Quad2D();

	void Draw() const;

	bool ClickCollision(float cursorX, float cursorY) const;

	void BindShader() const;

	std::vector<glm::vec3> GetInitialPosition() const;

	// Uniform Setters
	void SetUniform1f(const std::string& name, float value) const;
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) const;
};