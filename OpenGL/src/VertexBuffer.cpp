#include "Buffer.h"

#include <GL\glew.h>

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	glGenBuffers(1, &m_RendererID);
	this->SetData(data, size);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

inline uint32_t VertexBuffer::GetObjectID() const
{
	return m_RendererID;
}

inline void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

inline void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

inline void VertexBuffer::SetData(const void* data, const uint32_t size)
{
	this->Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}