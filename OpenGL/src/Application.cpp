#include "stdpch.h"

#include "VertexBufferLayout.h"
#include "Window.h"
#include "Renderer.h"
#include "Quad2D.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// GLOBAL VARIABLES (AKA STATE VARIABLES)
bool startRendering = false;
bool rickAstley = false;
std::vector<std::unique_ptr<Quad2D>> quadList;
float xOffset = 0.0f, yOffset = 0.0f;
glm::mat4 proj = glm::mat4(0.0f);
glm::mat4 mvp = glm::mat4(0.0f);



int main()
{
	// window lives through out this main scope allowing unique_ptr to clean up and avoid glfwTerminating twice
	std::unique_ptr<Window> window = std::unique_ptr<Window>(Window::Create());

	Renderer renderer(window->GetWindowHandle());

	// Test Commit 3

	WindowProps windowProperties = { "SandBox", 800, 600 };
	
	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		float vertices[] = {
			// positions	 // texture coords(bottom left is 0,0) 
			250.0f, 250.0f,		0.0f, 0.0f, 	// 0 bottom left
			500.0f, 250.0f,		1.0f, 0.0f,		// 1 bottom right
			500.0f, 500.0f,		1.0f, 1.0f,		// 2 top right
			250.0f, 500.0f,		0.0f, 1.0f		// 3 top left

		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		
		glm::vec2 quadOneCenter = { 100.0f,  200.0f };
		glm::vec2 quadTwoCenter = { 200.0f,  200.0f };
		glm::vec2 quadThreeCenter = { 300.0f,  500.0f };



		quadList.push_back(std::make_unique<Quad2D>(quadOneCenter, static_cast<float>(windowProperties.Width / 15.0f), static_cast<float>(windowProperties.Height / 10.0f), std::string("./res/textures/NGGYU.png")));

		quadList.push_back(std::make_unique<Quad2D>(quadTwoCenter, static_cast<float>(windowProperties.Width / 15.0f), static_cast<float>(windowProperties.Height / 25.0f), std::string("./res/textures/greyTile.png")));

		quadList.push_back(std::make_unique<Quad2D>(quadThreeCenter, static_cast<float>(windowProperties.Width / 15.0f), static_cast<float>(windowProperties.Height / 15.0f), std::string("./res/textures/awwsomeFace.png")));


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
		
		
		Shader defaultShader("./res/shader/default.shader");
		Shader shader("./res/shader/shader.shader");

		Texture happyFace("./res/textures/awesomeface.png");
		Texture rick("./res/textures/NGGYU.png");


		shader.Bind();
		//0 is the slot that the texture is bound to
		shader.SetUniform1i("u_Texture", 0);

		proj = glm::ortho(0.0f, (float)windowProperties.Width, 0.0f, (float)windowProperties.Height);

		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

		renderer.SetSpeed(1.0f);

		// Render Loop
		// -------------------
		while (!renderer.EndRenderLoop())
		{
			if (startRendering)
			{
				if (rickAstley)
					rick.Bind();
				else
					happyFace.Bind();

				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(xOffset, yOffset, 0.0f));

				glm::mat4 mvp = proj * view * model;

				shader.Bind();
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.ClearScreen();
				renderer.Draw(VA, IBO, shader);

			}
			else
			{
				///TODO: move clearscreen into window class?
				renderer.ClearScreen();
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(xOffset, yOffset, 0.0f));

				mvp = proj * view * model;

				for (const auto& quad : quadList)
				{
					quad->BindShader();
					quad->SetUniformMat4f("u_MVP", mvp);
					quad->Draw();
				}
				
			}
			window->OnUpdate();

		}
	}

	return 0;
}