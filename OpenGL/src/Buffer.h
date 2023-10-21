#pragma once

#include "Assert.h"
#include <iostream>

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
	/// </summary>
	/// <param name="data">pointer to the array of vertices</param>
	/// <param name="size">size of the array data (size)</param>
	void SetData(const void* data, const unsigned int size);
private:
	unsigned int m_RendererID;
};


class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int size);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	/// <summary>
	/// Copies the provided array of indices to the Buffer
	/// Also it automatically binds the IBO associated with it before copying the data
	/// 
	/// </summary>
	/// <param name="data">pointer to the array of indices</param>
	/// <param name="size">size of the element buffer array</param>
	void SetData(const unsigned int* data, const unsigned int size);

	unsigned int GetCount() const;

	unsigned int GetObjectID() const;

private:
	unsigned int m_RendererID, m_count;
};