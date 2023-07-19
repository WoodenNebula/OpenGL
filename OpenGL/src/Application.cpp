#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{

	Renderer::Init(3, 3);
	unsigned int width = 800, height = 600;
	Window* window = Renderer::CreateWindow(width, height, "Window");


	Renderer::SetViewPort(800, 600);
	// Texture - Black [0.0f, 0.5f)
	// Texture - White [0.5f, 0.5f]

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {
		0, 1, 2,
		3, 2, 1
	};

	{
		 /*Normal Pipeline of the program
		 VAO must be bound first
		 then VBO bind and set data
		 then EBO/IBO bind and set data
		 then configure vertex attributes*/

		Shader shader("./res/shader/shader.shader");

		VertexArrayObject VAO;

		VertexBuffer VBO(vertices, sizeof(vertices));
		IndexBuffer IBO(indices, sizeof(indices));

		// Position attrib
		VAO.ConfigureVertexAttribPointer(0, 3, 5 * sizeof(float), (void*)0);
		// Texture attrib
		VAO.ConfigureVertexAttribPointer(1, 2, 5 * sizeof(float), (void*)(5 * sizeof(float)));


		// Generating Textures
		// -------------------
		glActiveTexture(GL_TEXTURE0);

		unsigned int texID;
		GLCall(glGenTextures(1, &texID));
		GLCall(glBindTexture(GL_TEXTURE_2D, texID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		// Loading image
		stbi_set_flip_vertically_on_load(true);
		int imgWidth, imgHeight, imgChannels;
		unsigned char* happyFace = stbi_load("./res/textures/blackTile.png", &imgWidth, &imgHeight, &imgChannels, 0);

		if (happyFace)
		{
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, happyFace));
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		}
		else std::cout << "[ERROR] : Couldn't load texture data" << std::endl;

		stbi_image_free(happyFace);

		shader.UseShaderProgram();

		GLCall(glUniform1i(shader.GetUniformLocation("happyFace"), 0));


		Renderer::LineMode(false);

		// Render Loop
		// -------------------
		while (!Renderer::EndRenderLoop(window))
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texID);

			/* Render here */
			Renderer::ProcessInput(window);
			Renderer::Draw(VAO, VBO, IBO, shader, window);
		}


	}
	Renderer::Exit();

	return 0;
}