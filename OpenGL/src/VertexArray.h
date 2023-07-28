#pragma once

#include "Buffer.h"

class  VertexBufferLayout;

class VertexArray
{
private:
	uint32_t m_VAO_ID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};