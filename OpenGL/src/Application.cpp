#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Callbacks.h"
#include "Renderer.h"
#include "Texture.h"

bool startRendering = false;


struct Coord2D
{
	uint32_t x;
	uint32_t y;
};

//class Quad2D
//{
//public:
//
//	/// <summary>
//	/// Generates a Quad in 2D space at the specified position with diameter scaled by given scalar
//	/// </summary>
//	/// <param name="center">Position at screen space(pixel) at which the quad will have its center</param>
//	/// <param name="scale"></param>
//	Quad2D(WindowHint dimensions, const Coord2D& center = {0, 0}, uint32_t scale = 1)
//		:m_center(center), m_scale(scale)
//	{
//		GenerateVertices();
//
//	}
//private:
//	const uint32_t MIN_RADIUS = 5;
//
//	Coord2D m_center;
//	uint32_t m_scale;
//
//	float m_vertices[4 * 2];
//
//	Shader* QuadShader;
//	VertexBuffer* m_VB;
//	IndexBuffer* m_IB;
//	VertexBufferLayout* m_layout;
//
//	void GenerateVertices() 
//	{
//		m_vertices[0] = m_center.x; //	Top Left
//		m_vertices[1] = 0.0f;//	Top Right
//		m_vertices[2] = 0.0f;//	Bottom Right
//		m_vertices[3] = 0.0f;//	Bottom Left
//
//	}
//
//	
//	//void UseQuad()
//	//{
//	//	QuadShader("./res/shader/shader.shader");
//
//	//	VertexBuffer VBO(vertices, sizeof(vertices));
//	//	IndexBuffer IBO(indices, sizeof(indices));
//	//	VertexBufferLayout layout;
//
//	//	layout.Push<float>(2);	//pos
//	//	VA.AddBuffer(VBO, layout);
//
//	//	shader.Bind();
//	//}
//};



int main()
{
	Renderer renderer;

	renderer.InitGLFW(4, 3);
	
	WindowHint windowHint = { 800, 600 , "MAGIC", 800, 600};
	renderer.CreateWindow(windowHint);
	renderer.SetViewPort(windowHint.viewWidth, windowHint.viewHeight);
	
	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		float vertices[] = {
			// positions  // texture coords(bottom left is 0,0) 
			-0.5f, -0.5f,	0.0f, 0.0f, 	// 0 bottom left
			 0.5f, -0.5f,	1.0f, 0.0f,		// 1 bottom right
			 0.5f,  0.5f,	1.0f, 1.0f,		// 2 top right
			-0.5f,  0.5f,	0.0f, 1.0f,		// 3 top left

		};

		uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		 /*Normal Pipeline of the program
		 VA must be bound first
		 then VBO bind and set data
		 then EBO/IBO bind and set data
		 then configure vertex attributes*/

		Shader defaultShader("./res/shader/default.shader");
		Shader shader("./res/shader/shader.shader");

		VertexArray VA;
		VertexBuffer VBO(vertices, sizeof(vertices));
		IndexBuffer IBO(indices, sizeof(indices));
		VertexBufferLayout layout1;

		layout1.Push<float>(2);	//pos
		layout1.Push<float>(2);	//tex
		VA.AddBuffer(VBO, layout1);
		
		shader.Bind();

		Texture happyFace("./res/textures/awesomeface.png");
		happyFace.Bind();
		//0 is the slot that the texture is bound to
		shader.SetUniform1i("u_Texture", 0);


		// Render Loop
		// -------------------
		while (!renderer.EndRenderLoop())
		{
			if (startRendering)
			{
				float time = glfwGetTime();
				{
					renderer.ClearScreen();
					shader.Bind();
					//shader.SetUniform4f("offset", sin(time) / 2, cos(time), 0.0f, 1.0f);
					shader.SetUniform4f("offset", 0.0f, 0.0f, 0.0f, 1.0f);

					renderer.Draw(VA, IBO, shader);
				}
			}
			else {
				{
					renderer.ClearScreen();
					renderer.Draw(VA, IBO, defaultShader);
				}
			}


			renderer.ProcessInput();
		}


	}
	renderer.Exit();

	return 0;
}