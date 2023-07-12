#pragma once

#include "ErrorHandler.h"

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	/// <summary>
	/// Copies the provided array of indices to the Buffer
	/// Also it automatically binds the IBO associated with it before copying the data
	/// 
	/// </summary>
	/// <param name="data">pointer to the array of indices</param>
	/// <param name="count">number of elements within the array data (count)</param>
	void SetData(const unsigned int* data, const unsigned int count);

private:
	unsigned int m_RendererID;
};

