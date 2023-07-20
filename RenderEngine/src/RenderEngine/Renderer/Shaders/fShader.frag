#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

in vec3 norm;
in vec3 FragPos;
in vec2 TexCoord;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform sampler2D ourTexture;
uniform Material material;
uniform Light light;


void main()
{
	// Ambient lighting
	vec3 ambient = light.ambient * material.ambient;

	// Diffuse lighting
	vec3 fragNorm = normalize(norm);
	vec3 lightDir = normalize(light.position - FragPos);

	float diffValue = max(dot(norm, lightDir),0);
	vec3 diffuse =  light.diffuse * (diffValue * material.diffuse);

	//Specular lighting
	vec3 cameraDir = normalize(cameraPos - FragPos);
	vec3 reflecDir = reflect(-lightDir, fragNorm);
	
	float specValue = pow(max(dot(cameraDir, reflecDir), 0.0), 64);
	vec3 specular = (material.specular * specValue) * light.specular;

	FragColor = vec4((specular + diffuse + ambient) * objectColor , 1.0);
	//FragColor = texture(ourTexture, TexCoord);
}