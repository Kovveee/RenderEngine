#version 330 core
layout (location = 0) in vec3 Position;

out vec3 TexCoords;

uniform mat4 projMat;
uniform mat4 viewMat;

void main()
{
    TexCoords = Position;
    gl_Position = projMat * viewMat * vec4(Position, 1.0);
}  