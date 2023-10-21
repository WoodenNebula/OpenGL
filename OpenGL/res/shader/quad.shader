#shader vertex
#version 430 core

layout(location = 0) in vec4 positions;      
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(positions.x, positions.y, positions.z, 1.0f);
    v_TexCoord = texCoord;
}

#shader fragment
#version 430 core

in vec2 v_TexCoord;
out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    FragColor = texColor;
}
