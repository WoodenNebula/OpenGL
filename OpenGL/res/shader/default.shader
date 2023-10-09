#shader vertex
#version 430 core
layout(location = 0) 
in vec4 positions;

out vec4 vColor;

void main()
{
    gl_Position = positions;
    vColor = vec4(1.0f);
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
