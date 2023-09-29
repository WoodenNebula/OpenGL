#shader vertex
#version 430 core
layout(location = 0) in vec4 vertices;

void main()
{
    gl_Position = vertices;
}

#shader fragment
#version 430 core
out vec4 FragColor;

uniform vec4 iColor;

void main()
{
    FragColor = iColor;
}
