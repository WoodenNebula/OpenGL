#include "Buffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int size)
	:m_RendererID(0)
{
	GLCall(glGenBuffers(1, &m_RendererID));

	this->count = size / (sizeof(unsigned int));

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

inline void IndexBuffer::SetData(const unsigned int* data, const unsigned int size)
{
	this->Bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	//this->UnBind();
}