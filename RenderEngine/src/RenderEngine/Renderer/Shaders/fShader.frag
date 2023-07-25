#version 330 core



struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct DirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


struct Light
{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);


out vec4 FragColor;

in vec3 norm;
in vec3 FragPos;
in vec2 TexCoord;

uniform vec3 objectColor;
uniform vec3 cameraPos;
uniform sampler2D ourTexture;
uniform Material material;
uniform Light lightsource;
uniform PointLight light;

uniform DirLight directionalLights[10];

void main()
{

	/*float ldistance = length(light.position - FragPos);
	float attenuation = 1.0/(light.constant + light.linear * ldistance + light.quadratic * (ldistance * ldistance));
	// Ambient lighting
	vec3 ambient = light.ambient * material.ambient *attenuation;

	// Diffuse lighting
	vec3 fragNorm = normalize(norm);
	vec3 lightDir = normalize(light.position - FragPos);
	//vec3 lightDir = normalize(-light.direction); 

	

	float diffValue = max(dot(norm, lightDir),0);
	vec3 diffuse =  light.diffuse * (diffValue * material.diffuse) * attenuation;

	//Specular lighting
	vec3 cameraDir = normalize(cameraPos - FragPos);
	vec3 reflecDir = reflect(-lightDir, fragNorm);
	
	float specValue = pow(max(dot(cameraDir, reflecDir), 0.0), 64);
	vec3 specular = (material.specular * specValue) * light.specular * attenuation;

	FragColor = vec4((specular + diffuse + ambient) * objectColor , 1.0);
	//FragColor = texture(ourTexture, TexCoord);*/
	
	vec3 outputColor = vec3(0.0);
	vec3 cameraDir = normalize(cameraPos - FragPos);
	vec3 fragNorm = normalize(norm);

	for(int i = 0; i < 10; ++i)
		outputColor += CalcDirLight(directionalLights[i], fragNorm, cameraDir);

	FragColor = vec4(outputColor,1.0);

}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	float diffValue = max(dot(normal, lightDir),0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float specValue = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);

	vec3 ambient = light.ambient * material.diffuse;
	vec3 diffuse = light.diffuse * diffValue * material.diffuse;
	vec3 specular = light.specular * specValue * material.specular;

	return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	float lightDistance = length(light.position - FragPos);
	float attenuation = 1.0/(light.constant + light.linear * lightDistance + light.quadratic * (lightDistance * lightDistance));
	
	vec3 lightDir = normalize(light.position - FragPos);

	float diffValue = max(dot(normal, lightDir),0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float specValue = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);

	vec3 ambient = light.ambient * material.diffuse;
	vec3 diffuse = light.diffuse * diffValue * material.diffuse;
	vec3 specular = light.specular * specValue * material.specular;
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - FragPos);

	float theta = dot(lightDir,normalize(-light.direction));

	if(theta > light.cutOff)
	{
		float diffValue = max(dot(normal, lightDir),0.0);

		vec3 reflectDir = reflect(-lightDir, normal);
		float specValue = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);

		vec3 ambient = light.ambient * material.diffuse;
		vec3 diffuse = light.diffuse * diffValue * material.diffuse;
		vec3 specular = light.specular * specValue * material.specular;
		return (ambient + diffuse + specular);
	}
	else
		return vec3(light.ambient * material.ambient);
		
}