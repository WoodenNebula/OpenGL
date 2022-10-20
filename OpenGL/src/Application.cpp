
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type); //Creating id of a Shader of "type"
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //Error Handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);  //Getting length of log message in "length"

        char* message = (char*)_malloca(length * sizeof(char)); //Making a string of length "length" somehow

        glGetShaderInfoLog(id, length, &length, message);   //Actual error message being written on "message"

        std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader" << std::endl;
        std::cout << message << std::endl;

        //Handle the error
        glDeleteShader(id);
        return 0; //Cant return -1 since outside main function
    }

    return id;
}

static unsigned int CreateShaders(const std::string& vertexShader, const std::string fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "TRIANGLE", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Check if the GL Context is valid or not */
    if (glewInit() != GLEW_OK)
        std::cout << "Error Detected \n";
    
    /* Print out the current version of GL */
    std::cout << glGetString(GL_VERSION) << std::endl;

    float posTriangle[6] = {
        -0.5f, -0.5,
         0.0f,  0.5f,
         0.5f, -0.5f
    };
    
    unsigned int bufferOne;
        //This returns an id
    glGenBuffers(1, &bufferOne);
        //Selecting the above buffer
    glBindBuffer(GL_ARRAY_BUFFER, bufferOne);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    //Adding Data in the buffer 
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), posTriangle, GL_STATIC_DRAW);

    std::string vertexShader =
        "#version 410 core\n"
        "layout(location = 0) in vec4 position;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

    std::string fragmentShader =
        "#version 410 core\n"
        "layout(location = 0) out vec4 color;\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
        "}\n";


    unsigned int shader = CreateShaders(vertexShader, fragmentShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        // DrawCall
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
            
        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}