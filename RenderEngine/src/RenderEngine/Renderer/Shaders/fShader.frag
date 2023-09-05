#version 330 core


in vShaderOut
{
  vec3 norm;
  vec3 FragPos;
  vec2 TexCoord;
} fsIn;

out vec4 FragColor;


struct Material
{
	sampler2D diffuse;
	sampler2D specular;
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

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);

uniform vec3 cameraPos;

uniform Material material;

uniform int pointLightNum;
uniform int dirLightNum;

uniform DirLight directionalLights[10];
uniform PointLight pointLights[10];

void main()
{		
	vec3 outputColor = vec3(0.0);
	vec3 cameraDir = normalize(cameraPos - fsIn.FragPos);
	vec3 fragNorm = normalize(fsIn.norm);


	for(int i = 0; i < dirLightNum; ++i)
		outputColor += CalcDirLight(directionalLights[i], fragNorm, cameraDir);

	for(int i = 0; i < pointLightNum; ++i)
		outputColor += CalcPointLight(pointLights[i], fragNorm, cameraDir);

	FragColor = vec4(outputColor,1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	float diffValue = max(dot(normal, lightDir),0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float specValue = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, fsIn.TexCoord));
	vec3 diffuse = light.diffuse * diffValue  * vec3(texture(material.diffuse, fsIn.TexCoord));
	vec3 specular = light.specular * specValue * vec3(texture(material.specular, fsIn.TexCoord));

	return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	float lightDistance = length(light.position - fsIn.FragPos);
	float attenuation = 1.0/(light.constant + light.linear * lightDistance + light.quadratic * (lightDistance * lightDistance));
	
	vec3 lightDir = normalize(light.position - fsIn.FragPos);

	float diffValue = max(dot(normal, lightDir),0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float specValue = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, fsIn.TexCoord));
	vec3 diffuse = light.diffuse * diffValue  * vec3(texture(material.diffuse, fsIn.TexCoord));
	vec3 specular = light.specular * specValue * vec3(texture(material.specular, fsIn.TexCoord));
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fsIn.FragPos);

	float theta = dot(lightDir,normalize(-light.direction));

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, fsIn.TexCoord));

	if(theta > light.cutOff)
	{
		float diffValue = max(dot(normal, lightDir),0.0);

		vec3 reflectDir = reflect(-lightDir, normal);
		float specValue = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);

		vec3 diffuse = light.diffuse * diffValue  * vec3(texture(material.diffuse, fsIn.TexCoord));
		vec3 specular = light.specular * specValue * vec3(texture(material.specular, fsIn.TexCoord));
		return (ambient + diffuse + specular);
	}
	else
		return ambient;
}