#include "Buffer.h"

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	this->SetData(data, size);
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

inline uint32_t VertexBuffer::GetObjectID() const
{
	return m_RendererID;
}

inline void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

inline void VertexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

inline void VertexBuffer::SetData(const void* data, const uint32_t size)
{
	this->Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	//this->UnBind();
}