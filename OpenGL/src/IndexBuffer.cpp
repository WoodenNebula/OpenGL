#include "Buffer.h"

#include <GL/glew.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int size)
	:m_RendererID(0)
{
	glGenBuffers(1, &m_RendererID);

	this->m_count = size / (sizeof(unsigned int));

	this->SetData(data, size);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

inline void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

inline void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

inline void IndexBuffer::SetData(const unsigned int* data, const unsigned int size)
{
	this->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

unsigned int IndexBuffer::GetCount() const { return m_count; }

unsigned int IndexBuffer::GetObjectID() const { return m_RendererID; };

