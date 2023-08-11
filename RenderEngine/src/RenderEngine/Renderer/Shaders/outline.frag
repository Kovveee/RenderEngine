#version 330 core
out vec4 FragColor;

in vec3 norm;
in vec3 FragPos;


uniform vec3 color;
uniform vec3 cameraPos;


vec3 lightColor = vec3(1);
vec3 lightPos = vec3(0,10,0);

void main()
{
	
	vec3 ambient = 0.1 * lightColor;

	vec3 normal = normalize(norm);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffValue = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diffValue * lightColor;


	FragColor = vec4((ambient + diffuse)*color,1.0);
}