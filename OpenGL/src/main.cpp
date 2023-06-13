#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearErrors();\
	x;\
	ASSERT(GLLogCall(#x, __LINE__, __FILE__))


/* Reset all the error flags previously raised/unattended */
static void GLClearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

///
/// Converts the GLenum error codes into string error messages
/// 
static const char* GLEnumErrorDecoder(GLenum error)
{
	if (error == GL_INVALID_ENUM)
		return "GL_INVALID_ENUM";
	else if (error == GL_INVALID_VALUE)
		return "GL_INVALID_VALUE";
	else if (error == GL_INVALID_OPERATION)
		return "GL_INVALID_OPERATION";
	else if (error == GL_INVALID_FRAMEBUFFER_OPERATION)
		return "GL_INVALID_FRAMEBUFFER_OPERATION";
	else if (error == GL_OUT_OF_MEMORY)
		return "GL_OUT_OF_MEMORY";
}

static bool GLLogCall(const char* functionName, int line, const char* file)
{
	while (GLenum errorCode = glGetError())
	{
		std::cout << "[Error] : " << line << " from " << functionName << " -> " 
			<< errorCode << " \n\t" << GLEnumErrorDecoder(errorCode) << " : " << file << std::endl;
		return false;
	}
	return true;
}

//TODO: create a shader compile funciton

/* creates a shader program that has to be attached and linked */
static uint32_t CreateShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc)
{
	uint32_t vertexShader;
	GLCall(vertexShader = glCreateShader(GL_VERTEX_SHADER));
	GLCall(glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL));
	GLCall(glCompileShader(vertexShader));

	int success;
	char infoLog[512];
	GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));

	if (!success)
	{
		GLCall(glGetShaderInfoLog(vertexShader, 512, NULL, infoLog));
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}


	uint32_t fragmentShader;
	GLCall(fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
	GLCall(glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL));
	GLCall(glCompileShader(fragmentShader));

	GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));

	if (!success)
	{
		GLCall(glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog));
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}

	GLCall(uint32_t shaderProgram = glCreateProgram());

	GLCall(glAttachShader(shaderProgram, vertexShader));
	GLCall(glAttachShader(shaderProgram, fragmentShader));
	GLCall(glLinkProgram(shaderProgram));

	GLCall(glValidateProgram(shaderProgram));

	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));

	return shaderProgram;
}

int main()
{
	/* Initializing GLFW library */
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "[Error] : line " << __LINE__ << " from (" << "glfwInit" << ")"
			<< " -> " << GLFW_FALSE << "\n\tFailed to initialize glfw" << " : " << __FILE__ << std::endl;
		return -1;
	}

	/* Explicitly set the opengl version 3.3 (what we are using) */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	/* Explicitly set the opengl profile to core (what we are using) */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	/* Creating a Window object */
	GLFWwindow* window = glfwCreateWindow(800, 600, "HELLO", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "[Error] : line " << __LINE__ << " -> " << NULL << "\n\tWindow Creation Failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);


	/* Initializing GLEW library */
	if(glewInit() != GLEW_OK)
	{
		std::cout << "[Error] : GLEW initialization failed!" << std::endl;
		return -1;
	}

	/* Setting the size of the viewable area */
	GLCall(glViewport(0, 0, 800, 600));

	std::cout << glGetString(GL_VERSION) << std::endl;


	float vertices[] = {
		-0.5f, -0.5f, 0.0f,  
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	unsigned int VAO; 
	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glBindVertexArray(VAO));

	uint32_t buffer;
	GLCall(glGenBuffers(1, &buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(vertices), vertices, GL_STATIC_DRAW));

	GLCall(glEnableVertexAttribArray(0));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);



///
	std::fstream shaderSource(".\\res\\shader.shader");
	std::stringstream ss[2];
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	ShaderType type = ShaderType::NONE;
	std::string line;


	if (shaderSource.is_open())
	{

		while (std::getline(shaderSource, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::FRAGMENT;
				}
			}
			else
			{
				ss[(int)type] << line << "\n";
			}
		}
	}
///
	
	uint32_t shaderProgram = CreateShaderProgram(ss[0].str().c_str(), ss[1].str().c_str());
	
	GLCall(glUseProgram(shaderProgram));




	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
		

		/* Swap front and back buffers */
		GLCall(glfwSwapBuffers(window));

		/* Poll for events and processes */
		GLCall(glfwPollEvents());
	}
	

	glfwTerminate();
	return 0;
}