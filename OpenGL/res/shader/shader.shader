#shader vertex
#version 330 core
layout(location = 0) in vec4 vertices;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    gl_Position = vertices;
    TexCoord = aTexCoord;
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D happyFace;

void main()
{
    //FragColor = vec4(1.0f, 0.069f, 0.69f, 1.0f);
    FragColor = texture(happyFace, TexCoord);
}
