#include "Buffer.h"

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t size)
	:m_RendererID(0)
{
	GLCall(glGenBuffers(1, &m_RendererID));

	this->count = size / (sizeof(uint32_t));

	this->SetData(data, size);
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

inline void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

inline void IndexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

inline void IndexBuffer::SetData(const uint32_t* data, const uint32_t size)
{
	this->Bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	//this->UnBind();
}