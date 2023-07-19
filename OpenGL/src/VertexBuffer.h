#pragma once
#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include "ErrorHandler.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	unsigned int GetObjectID() const;

	void Bind() const;
	void UnBind() const;

	/// <summary>
	/// Copies the provided array of vertices to the Buffer
	/// Also it automatically binds the VBO associated with it before copying the data 
	/// 
	/// </summary>
	/// <param name="data">pointer to the array of vertices</param>
	/// <param name="size">size of the array data (size)</param>
	void SetData(const void* data, const unsigned int size);
private:
	unsigned int m_RendererID;
};

#endif // !VERTEX_BUFFER