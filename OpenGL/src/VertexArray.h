#pragma once

// Forward declarations to avoid including the headers
class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
private:
	uint32_t m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};