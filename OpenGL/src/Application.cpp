#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Quad2D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <vector>
#include <memory>


// GLOBAL VARIABLES (AKA STATE VARIABLES)
bool startRendering = false;
bool rickAstley = false;
std::vector<std::unique_ptr<Quad2D>> quadList;


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
			// positions	 // texture coords(bottom left is 0,0) 
			250.0f, 250.0f,		0.0f, 0.0f, 	// 0 bottom left
			500.0f, 250.0f,		1.0f, 0.0f,		// 1 bottom right
			500.0f, 500.0f,		1.0f, 1.0f,		// 2 top right
			250.0f, 500.0f,		0.0f, 1.0f,		// 3 top left

		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		
		Coord2D quadOneCenter = { 100.0f,  200.0f };
		Coord2D quadTwoCenter = { 200.0f,  200.0f };
		Coord2D quadThreeCenter = { 300.0f,  500.0f };



		quadList.push_back(std::make_unique<Quad2D>(windowHint, quadOneCenter, static_cast<float>(windowHint.width / 15.0f), static_cast<float>(windowHint.height / 10.0f), std::string("./res/textures/NGGYU.png")));

		quadList.push_back(std::make_unique<Quad2D>(windowHint, quadTwoCenter, static_cast<float>(windowHint.width / 15.0f), static_cast<float>(windowHint.height / 25.0f), std::string("./res/textures/greyTile.png")));

		quadList.push_back(std::make_unique<Quad2D>(windowHint, quadThreeCenter, static_cast<float>(windowHint.width / 15.0f), static_cast<float>(windowHint.height / 15.0f), std::string("./res/textures/awwsomeFace.png")));


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
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));

		glm::mat4 mvp = proj * view * model;

		for (const auto& quad : quadList)
		{
			quad->BindShader();
			quad->SetUniformMat4f("u_MVP", mvp);
		}

		
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
				if (rickAstley)
					rick.Bind();
				else
					happyFace.Bind();

				renderer.ClearScreen();
				renderer.Draw(VA, IBO, shader);

			}
			else
			{
				renderer.ClearScreen();
				for (const auto& quad : quadList)
				{
					quad->Draw();
				}
				

				//renderer.SetBackGroundColor(glm::vec3(0.0912f));
				//for (const auto& quad : quadList)
			}

			/* Swap front and back buffers */
			glfwSwapBuffers(renderer.GetWindow());

			/* Poll for events and processes */
			glfwPollEvents();

			//renderer.ProcessInput();
		}
	}
	renderer.Exit();

	return 0;
}