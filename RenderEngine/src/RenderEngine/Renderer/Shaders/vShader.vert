#version 330

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


out vShaderOut
{
  vec3 norm;
  vec3 FragPos;
  vec2 TexCoord;
} vOut;


void main()
{
	gl_Position = projection * view * worldMat * vec4(Position,1.0);
	vOut.norm = mat3(worldIT) * Normals;
	vOut.FragPos =  (worldMat * vec4(Position,1.0)).xyz;
	vOut.TexCoord = Texture;
}