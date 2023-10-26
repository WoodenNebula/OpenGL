#include "stdpch.h"

#include "Quad2D.h"

#include "VertexArray.h"
#include "Buffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

Quad2D::Quad2D(const WindowHint& dimensions, const Coord2D& center, float width, float height, const std::string& texturePath)
	:m_Dimensions(dimensions), m_Center(center), m_width(width), m_height(height), m_vertices{
		// Positions										// Texture coord (Bottom left is 0,0)
		m_Center.x - m_width, m_Center.y + m_height,		0.0f, 1.0f,			// 0 Top Left
		m_Center.x + m_width, m_Center.y + m_height,		1.0f, 1.0f,			// 1 Top Right
		m_Center.x + m_width, m_Center.y - m_height,		1.0f, 0.0f,			// 2 Bottom Right
		m_Center.x - m_width, m_Center.y - m_height,		0.0f, 0.0f			// 3 Bottom Left
	}, 
	m_initialPosition{
	glm::vec3(m_vertices[0],  m_vertices[1], 0.0f),	// 0
	glm::vec3(m_vertices[4],  m_vertices[5], 0.0f),	// 1
	glm::vec3(m_vertices[8],  m_vertices[9], 0.0f),	// 2
	glm::vec3(m_vertices[12], m_vertices[13], 0.0f) // 3
	}, 
	m_indices{
			0, 1, 2,
			2, 3, 0
	}
{
	m_VA = std::make_unique<VertexArray>();

	m_VB = std::make_unique<VertexBuffer>(m_vertices, sizeof(m_vertices));
	m_IB = std::make_unique<IndexBuffer>(m_indices, sizeof(m_indices));

	m_Layout = std::make_unique<VertexBufferLayout>();
	m_Layout->Push<float>(2);	//pos
	m_Layout->Push<float>(2);	//texture

	m_VA->AddBuffer(*m_VB, *m_Layout);

	m_QuadShader = std::make_unique<Shader>("./res/shader/quad.shader");
	m_Texture = std::make_unique<Texture>(texturePath);
}


Quad2D::~Quad2D() {}


void Quad2D::Draw() const
{
	m_QuadShader->Bind();
	m_VA->Bind();
	m_VB->Bind();
	m_IB->Bind();
	m_Texture->Bind();

	///
	/// Primitive(shape) we want to use
	/// How many indices we want to draw
	/// Data type of indices
	/// Index of indices 
	///
	glDrawElements(GL_TRIANGLES, m_IB->GetCount(), GL_UNSIGNED_INT, 0);

}

std::vector<glm::vec3> Quad2D::GetInitialPosition() const
{
	return m_initialPosition;
}

bool Quad2D::ClickCollision(float cursorX, float cursorY) const
{
	extern glm::mat3 mvp;


	if ((cursorX >= m_Center.x - m_width && cursorX <= m_Center.x + m_width) &&
		(cursorY >= m_Center.y - m_height && cursorY <= m_Center.y + m_height))
	{
		return true;
	}
	else return false;
}


void Quad2D::BindShader() const
{
	m_QuadShader->Bind();
}


void Quad2D::SetUniform1f(const std::string& name, float value) const
{
	m_QuadShader->SetUniform1f(name, value);
}


void Quad2D::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const
{
	m_QuadShader->SetUniform4f(name, v0, v1, v2, v3);
}


void Quad2D::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) const
{
	m_QuadShader->SetUniformMat4f(name, matrix);
}
