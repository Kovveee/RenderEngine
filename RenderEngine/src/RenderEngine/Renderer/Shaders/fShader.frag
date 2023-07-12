#version 330 core
out vec4 color;

uniform vec3 colorChange;

void main()
{
	color = vec4(colorChange,1.0);
}