#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normals;
layout (location = 2) in vec2 Texture;
layout (location = 3) in vec3 Tangents;

uniform mat4 worldMat;
uniform mat4 worldIT;

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
	mat4 lightSpaceMatrix;
};


out vShaderOut
{
  vec3 norm;
  vec3 FragPos;
  vec2 TexCoord;
  vec4 FragPosLightSpace;
  mat3 TBN;
} vOut;


void main()
{
	gl_Position = projection * view * worldMat * vec4(Position,1.0);
	vOut.norm = mat3(worldIT) * Normals;
	vOut.FragPos =  (worldMat * vec4(Position,1.0)).xyz;
	vOut.TexCoord = Texture;
	vOut.FragPosLightSpace = lightSpaceMatrix * vec4(vOut.FragPos,1.0);
	vec3 T = normalize(vec3(worldMat * vec4(Tangents,0.0)));
	vec3 N = normalize(vec3(worldMat * vec4(Normals, 0.0)));
	T = normalize(T - dot(T, N)*N);

	vec3 B = cross(N,T);
	vOut.TBN = mat3(T,B,N);

}