#include "Renderer.h"

#include <iostream>

Renderer::Renderer(GLFWwindow* Window) : m_window(Window) {}

Renderer::~Renderer() {}

bool Renderer::EndRenderLoop() { return glfwWindowShouldClose(m_window); }

void Renderer::LineMode(bool drawInLineMode = false) {
    if (drawInLineMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void Renderer::ClearScreen() {
    /* Clean and assign new color to back buffer*/
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SetBackGroundColor(const glm::vec3& Color) {
    glClearColor(Color.r, Color.g, Color.b, 1.0f);
}

void Renderer::Draw(const VertexArray& VA, const IndexBuffer& IBO,
                    const Shader& shader) {
    /* Color of background of window */
    glClearColor(0.2f, 0.39f, 0.32f, 1.0f);

    shader.Bind();
    VA.Bind();
    IBO.Bind();

    ///
    /// Primitive(shape) we want to use
    /// How many indices we want to draw
    /// Data type of indices
    /// Index of indices
    ///
    glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::Exit() { glfwTerminate(); }