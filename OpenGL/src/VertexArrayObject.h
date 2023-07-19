#pragma once
#ifndef VERTEX_ARRAY
#define VERTEX_ARRAY

#include "ErrorHandler.h"

class VertexArrayObject
{
public:
	///Generate a Vertex Array Object for opengl to use
	VertexArrayObject();
	~VertexArrayObject();

	void EnableVAO(unsigned int attribIndex) const;

	void Bind() const;
	void UnBind() const;

	/// <summary>
	/// Tells OpenGL how the data within a vertex is arranged in the GPU buffer
	/// and automatically enables the VAO
	/// </summary>
	/// <param name="attribIndex">: Position of Vertex Attribute within a vertex(position, texture coord, color, etc)</param>
	/// <param name="vertexElementCount">: No. of floats per vertex</param>
	/// <param name="strideSize">: Size of data between same attribute from consecutive vertices(position1 to position2)</param>
	/// <param name="attribOffset">: Offset of the vertex attrib within the vertex (if vertex has 3d position and color, then the offset for color will be different)</param>
	void ConfigureVertexAttribPointer(const unsigned int attribIndex, const unsigned int vertexElementCount, const unsigned int strideSize, void* attribOffset);
private:
	unsigned int m_VAO_ID;
};

#endif // !VERTEX_ARRAY