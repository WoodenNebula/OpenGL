#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	GLCall(glGenVertexArrays(1, &m_VAO_ID));
	this->Bind();
}

VertexArrayObject::~VertexArrayObject()
{
	GLCall(glDeleteVertexArrays(1, &m_VAO_ID));
}

void VertexArrayObject::EnableVAO(unsigned int attribIndex) const
{
	GLCall(glEnableVertexAttribArray(attribIndex));
}

void VertexArrayObject::Bind() const
{
	GLCall(glBindVertexArray(m_VAO_ID));
}

void VertexArrayObject::UnBind() const
{
	GLCall(glBindVertexArray(0));
}

void VertexArrayObject::ConfigureVertexAttribPointer(const unsigned int attribIndex, const unsigned int vertexElementCount, const unsigned int strideSize, void* attribOffset)
{
	GLCall(glVertexAttribPointer(attribIndex, vertexElementCount, GL_FLOAT, GL_FALSE, strideSize, attribOffset));
	this->EnableVAO(attribIndex);
}
