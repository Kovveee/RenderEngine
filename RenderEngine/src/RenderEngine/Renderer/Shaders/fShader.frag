#version 330 core
out vec4 FragColor;

in vec3 vs_out_norm;
in vec3 vs_out_FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

float ambientStrength = 0.1f;

void main()
{
	vec3 ambient = ambientStrength * lightColor;
	
	vec3 fragNorm = normalize(vs_out_norm);
	vec3 lightDir = normalize(lightPos - vs_out_FragPos);

	float diffValue = max(dot(vs_out_norm, lightDir), 0.0);
	vec3 diffuse = diffValue * lightColor;

	FragColor = vec4((ambient + diffuse) * objectColor, 1.0);
}