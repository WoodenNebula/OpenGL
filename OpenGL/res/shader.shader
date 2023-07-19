#shader vertex
#version 330 core
layout(location = 0) in vec4 vertices;
void main()
{
    gl_Position = vertices;
}

#shader fragment
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
