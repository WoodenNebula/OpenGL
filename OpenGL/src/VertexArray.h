#pragma once
typedef unsigned int uint32_t;

// Forward declarations to avoid including the headers
class VertexBuffer;
#include "VertexBufferLayout.h"

class VertexArray {
   private:
    uint32_t m_RendererID;

   public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const;
    void UnBind() const;
};