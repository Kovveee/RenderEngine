#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normals;
layout (location = 2) in vec2 Texture;

uniform mat4 worldMat;
uniform mat4 worldIT;

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
};


uniform float time;

void main()
{	float newY = (sin(time + Position.x * Position.z)) / 7;
    vec3 translatedPos  =  vec3(Position.x, newY, Position.z);
	gl_Position =  vec4(translatedPos, 1.0);
}