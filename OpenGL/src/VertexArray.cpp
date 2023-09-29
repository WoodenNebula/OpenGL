#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "ErrorHandler.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VAO_ID);
	glBindVertexArray(m_VAO_ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_VAO_ID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	this->Bind();
	vb.Bind();

	const auto& elements = layout.GetElements();
	uint32_t offset = 0;

	for (uint32_t i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (void *)offset);
		
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}


void VertexArray::Bind() const
{
	glBindVertexArray(m_VAO_ID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}