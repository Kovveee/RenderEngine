#version 330

in vec3 Position;
in vec3 Normals;

uniform mat4 worldMat;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform mat4 worldIt;

out vec3 vs_out_norm;
out vec3 vs_out_FragPos;

void main()
{
	gl_Position = projMat * viewMat * worldMat * vec4(Position,1.0);
	//vs_out_norm = (worldIt * vec4(Normals, 1.0)).xyz;
	vs_out_norm = Normals;
	vs_out_FragPos = vec3(worldMat * vec4(Position,1.0));
}