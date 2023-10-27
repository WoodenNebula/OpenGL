#pragma once

#include "Buffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int m_VAO_ID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};