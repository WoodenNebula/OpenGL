#shader vertex
#version 430 core
layout(location = 0) in vec4 positions;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
//out vec4 vColor;

uniform vec4 offset;
uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(positions.x + offset.x, positions.y + offset.y, positions.z, 1.0f);
    //vColor = vec4(1.0f+ offset.x * offset.y, 1.0f + offset.x, 1.0f + offset.y / 2, 1.0f);
    v_TexCoord = texCoord;
}

#shader fragment
#version 430 core
//in vec4 vColor;
in vec2 v_TexCoord;
out vec4 FragColor;

//uniform vec4 iColor;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    FragColor = texColor;
}
