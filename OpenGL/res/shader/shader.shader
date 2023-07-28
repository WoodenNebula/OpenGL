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

uniform vec4 iColor;

void main()
{
    FragColor = iColor;
}
