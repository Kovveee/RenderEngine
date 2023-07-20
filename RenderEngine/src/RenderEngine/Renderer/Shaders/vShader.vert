#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normals;
layout (location = 2) in vec2 Texture;

uniform mat4 worldMat;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform mat4 worldIT;

out vec3 norm;
out vec3 FragPos;
out vec2 TexCoord;

void main()
{
	gl_Position = projMat * viewMat * worldMat * vec4(Position,1.0);
	norm = mat3(worldIT) * Normals;
	FragPos =  (worldMat * vec4(Position,1.0)).xyz;
	TexCoord = Texture;
}