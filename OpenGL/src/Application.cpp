#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Callbacks.h"
#include "Renderer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

bool startRendering = false;
bool rickAstley = false;

struct Coord2D
{
	float x;
	float y;
};

class Quad2D
{
private:
	float m_radius = 10.0f;

	Coord2D m_Center;
	float m_scale;

	std::vector<float> m_vertices;

	unsigned int m_indices[2 * 3] = 
	{
		0, 1, 2,
		2, 3, 0 
	};

	Shader* QuadShader;
	VertexArray* m_VA;
	VertexBuffer* m_VB;
	IndexBuffer* m_IB;
	VertexBufferLayout* m_Layout;
	WindowHint m_Dimensions;

public:

	/// <summary>
	/// Generates a Quad in 2D space at the specified position with diameter scaled by given scalar
	/// </summary>
	/// <param name="center">Position at screen space(pixel) at which the quad will have its center</param>
	/// <param name="scale"></param>
	Quad2D(const WindowHint& dimensions, const Coord2D& center = { 0.0f, 0.0f }, uint32_t scale = 1)
		:m_Center(center), m_scale(scale), QuadShader(nullptr), m_VA(nullptr), m_VB(nullptr), m_Layout(nullptr), m_Dimensions(dimensions)
	{
		m_radius = m_radius * m_scale;
		GenerateVertices();

		m_VA = new VertexArray();
		/// Setting up for Render
		QuadShader = new Shader("./res/shader/quad.shader");

		m_VB = new VertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(float));
		m_IB = new IndexBuffer(m_indices, sizeof(m_indices));
		m_Layout = new VertexBufferLayout();
		m_Layout->Push<float>(2);	//pos
		m_VA->AddBuffer(*m_VB, *m_Layout);
	}

	~Quad2D()
	{
		delete m_Layout;
		delete m_IB;
		delete m_VB;
		delete QuadShader;
		delete m_VA;
	}

	/// TODO: Yet to be implemented Corrrrectly
	void Draw() const
	{
		///* Color of background of window */
		//glClearColor(0.78f, 0.89f, 0.53f, 1.0f);

		QuadShader->Bind();
		m_VA->Bind();
		m_VB->Bind();
		m_IB->Bind();

		///
		/// Primitive(shape) we want to use
		/// How many indices we want to draw
		/// Data type of indices
		/// Index of indices 
		///
		glDrawElements(GL_TRIANGLES, m_IB->GetCount(), GL_UNSIGNED_INT, 0);

		///* Swap front and back buffers */
		//glfwSwapBuffers(window);

		/* Poll for events and processes */
		glfwPollEvents();
	}

	VertexArray* GetVA() const { return m_VA; }
	IndexBuffer* GetIB() const { return m_IB; }
	Shader* GetShader() const { return QuadShader; }

private:
	void GenerateVertices() 
	{
		m_vertices.push_back(m_Center.x - m_radius);		//	0 TopLeft
		m_vertices.push_back(m_Center.y + m_radius);		//	0 TopLeft

		m_vertices.push_back(m_Center.x + m_radius);		//	1 TopRight
		m_vertices.push_back(m_Center.y + m_radius);		//	1 TopRight

		m_vertices.push_back(m_Center.x + m_radius);		//	2 BottomRight
		m_vertices.push_back(m_Center.y - m_radius);		//	2 BottomRight

		m_vertices.push_back(m_Center.x - m_radius);		//	3 BottomLeft
		m_vertices.push_back(m_Center.y - m_radius);		//	3 BottomLeft
	}
};



int main()
{
	Renderer renderer;

	renderer.InitGLFW(4, 3);
	
	WindowHint windowHint = { 800, 600 , "MAGIC", 800, 600};
	renderer.CreateWindow(windowHint);
	renderer.SetViewPort(windowHint.viewWidth, windowHint.viewHeight);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		float vertices[] = {
			// positions  // texture coords(bottom left is 0,0) 
			250.0f, 250.0f,	0.0f, 0.0f, 	// 0 bottom left
			500.0f, 250.0f,	1.0f, 0.0f,		// 1 bottom rightW
			500.0f, 500.0f,	1.0f, 1.0f,		// 2 top right
			250.0f, 500.0f,	0.0f, 1.0f,		// 3 top left

		};

		uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0
		};


		Quad2D randomQuad(windowHint, { windowHint.width/1.3f, windowHint.height/3.5f }, 7);


		/*Normal Pipeline of the program
		VA must be bound first
		then VBO bind and set data
		then EBO/IBO bind and set data
		then configure vertex attributes*/

		VertexArray VA;
		VertexBuffer VBO(vertices, sizeof(vertices));
		IndexBuffer IBO(indices, sizeof(indices));
		VertexBufferLayout layout1;

		layout1.Push<float>(2);	//pos
		layout1.Push<float>(2);	//tex
		VA.AddBuffer(VBO, layout1);
		
		glm::mat4 proj = glm::ortho(0.0f, (float)windowHint.width, 0.0f, (float)windowHint.width);
		//camera
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0.0f));

		glm::mat4 mvp = proj * view * model;

		randomQuad.GetShader()->Bind();
		randomQuad.GetShader()->SetUniformMat4f("u_MVP", mvp);

		
		Shader defaultShader("./res/shader/default.shader");
		Shader shader("./res/shader/shader.shader");
		shader.Bind();
		shader.SetUniformMat4f("u_MVP", mvp);


		Texture happyFace("./res/textures/awesomeface.png");
		Texture rick("./res/textures/NGGYU.png");


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
					if (rickAstley)
						rick.Bind();
					else
						happyFace.Bind();
					renderer.ClearScreen();
					shader.Bind();
					//shader.SetUniform4f("offset", sin(time) / 2, cos(time), 0.0f, 1.0f);
					shader.SetUniform4f("offset", 0.0f, 0.0f, 0.0f, 1.0f);

					renderer.Draw(VA, IBO, shader);

					//renderer.Draw(*randomQuad.GetVA(), *randomQuad.GetIB(), *randomQuad.GetShader());


				}
			}
			else 
			{
				{
					renderer.ClearScreen();
					//renderer.SetBackGroundColor(glm::vec3(0.0912f));
					//randomQuad.Draw();

					renderer.Draw(*randomQuad.GetVA(), *randomQuad.GetIB(), *randomQuad.GetShader());
				}
			}
			renderer.ProcessInput();
		}


	}
	renderer.Exit();

	return 0;
}