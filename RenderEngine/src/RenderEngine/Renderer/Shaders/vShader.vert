#version 330

in vec3 Position;
in vec3 Color;
			
void main()
{
	gl_Position = vec4(Position,1.0);
}