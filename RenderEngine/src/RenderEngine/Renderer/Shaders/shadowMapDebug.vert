#version 330 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normals;
layout (location = 2) in vec2 Texture;

out vec2 TexCoords;

void main()
{
    TexCoords = Texture;
    gl_Position = vec4(Position, 1.0);
}