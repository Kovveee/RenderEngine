#version 330 core
out vec4 FragColor;

in vec3 norm;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;


float ambientStrength = 0.1f;
float specularStrength = 0.5f;

void main()
{
	// Ambient lighting
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse lighting
	vec3 fragNorm = normalize(norm);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diffValue = max(dot(norm, lightDir),0);
	vec3 diffuse = diffValue * lightColor;

	//Specular lighting
	vec3 cameraDir = normalize(cameraPos - FragPos);
	vec3 reflecDir = reflect(-lightDir, fragNorm);
	
	float specValue = pow(max(dot(cameraDir, reflecDir), 0.0), 64);
	vec3 specular = specularStrength * specValue * lightColor;

	FragColor = vec4((specular + diffuse + ambient) * objectColor , 1.0);
}