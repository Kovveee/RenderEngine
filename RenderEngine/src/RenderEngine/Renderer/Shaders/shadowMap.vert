#version 330 core

layout (location = 0) in vec3 Position;

uniform mat4 lightSpaceMatrix;
uniform mat4 worldMat;

void main(){
	gl_Position = lightSpaceMatrix * worldMat  * vec4(Position, 1.0);
}