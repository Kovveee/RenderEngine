#version 330

in vec3 Position;
in vec3 Color;

uniform mat4 worldMat;
uniform mat4 viewMat;
uniform mat4 projMat;
			
void main()
{
	gl_Position = projMat * viewMat * worldMat * vec4(Position,1.0);
}