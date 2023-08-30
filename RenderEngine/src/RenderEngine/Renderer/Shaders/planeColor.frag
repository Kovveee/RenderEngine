#version 330 core
out vec4 FragColor;

uniform vec3 color;

in vec3 norm;
in vec3 FragPos;


void main()
{

	vec3 lightDir = normalize(vec3(0,1000,-500) - FragPos);

	vec3 fragNorm = normalize(norm);

	float diffValue = max(dot(fragNorm, lightDir),0.0);
	
	vec3 ambient = 0.1 * vec3(1, 1, 1);
	vec3 diffuse = vec3(1,1,1) * diffValue;
	vec3 result = (ambient + diffuse) * vec3(0.2, 0.8, 0.1);
	FragColor = vec4(result,1.0);
}