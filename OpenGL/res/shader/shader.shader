#shader vertex
#version 430 core
layout(location = 0) in vec4 positions;

uniform vec4 offset;
out vec4 vColor;

void main()
{
    gl_Position = vec4(positions.x + offset.x, positions.y * offset.y, positions.z, 1.0f);
    vColor = vec4(1.0f+ offset.x * offset.y, 1.0f + offset.x, 1.0f + offset.y / 2, 1.0f);
}

#shader fragment
#version 430 core
in vec4 vColor;
out vec4 FragColor;

//uniform vec4 iColor;

void main()
{
    FragColor = vColor;
}
