#version 330 core
layout (location = 0) in vec3 Position;

out vec3 TexCoords;

uniform mat4 projMat;
uniform mat4 viewMat;

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

void main()
{
    TexCoords = Position;
    gl_Position = projection * mat4(mat3(view)) * vec4(Position, 1.0);
}  