#version 330 core

in vShaderOut
{
  vec3 norm;
  vec3 FragPos;
  vec2 TexCoord;
  vec4 FragPosLightSpace;
  mat3 TBN;
} fsIn;

out vec4 FragColor;


struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normalMap;
	float shininess;
};

struct DirLight
{
	vec4 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

struct PointLight
{
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;

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
float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir, vec3 fragNorm);

uniform vec3 cameraPos;

uniform Material material;
uniform bool normalIsSet;

uniform int pointLightNum;  
uniform int dirLightNum;

uniform PointLight pointLights[10];

uniform sampler2D shadowMap;

const int pcfCount = 3;
const float totalTexels = (pcfCount * 2.0 + 1.0) * (pcfCount * 2.0 + 1.0);

layout (std140) uniform Lights
{
	DirLight directionLights[10];
	PointLight pointLights2[10];
};

void main()
{		
	vec3 outputColor = vec3(0.0);
	vec3 cameraDir = normalize(cameraPos - fsIn.FragPos);
	vec3 fragNorm;
	if(!normalIsSet){
		fragNorm = normalize(fsIn.norm);
	}
	else{
	    fragNorm = texture(material.normalMap, fsIn.TexCoord).rgb;
		fragNorm = fragNorm * 2.0 - 1.0;
		fragNorm = normalize(fsIn.TBN * fragNorm);
	}

	float gamma = 2.2f;

	for(int i = 0; i < dirLightNum; ++i)
		outputColor += CalcDirLight(directionLights[i], fragNorm, cameraDir);

	//for(int i = 0; i < pointLightNum; ++i)
		//outputColor += CalcPointLight(pointLights2[i], fragNorm, cameraDir);

	outputColor = pow(outputColor,vec3(1.0/gamma));
	FragColor = vec4(outputColor,1.0);
}
float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir, vec3 fragNorm){
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, projCoords.xy).r; 

    float currentDepth = projCoords.z;

	//float bias = max(0.05 * (1.0 - dot(fragNorm, lightDir)), 0.005);  

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -pcfCount; x <= pcfCount; ++x)
    {
        for(int y = -pcfCount; y <= pcfCount; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= totalTexels;

	if(projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	light.direction = -light.direction;
	vec3 lightDir = normalize(-vec3(light.direction));

	float diffValue = max(dot(normal, lightDir),0.0);

	vec3 halfwayDir = normalize(lightDir + viewDir);
	float specValue = pow(max(dot(normal, halfwayDir),0.0), material.shininess);

	vec3 ambient = vec3(light.ambient) * vec3(texture(material.diffuse, fsIn.TexCoord));
	vec3 diffuse = vec3(light.diffuse) * diffValue  * vec3(texture(material.diffuse, fsIn.TexCoord));
	vec3 specular = vec3(light.specular) * specValue * vec3(texture(material.specular, fsIn.TexCoord));

	float shadow = ShadowCalculation(fsIn.FragPosLightSpace, lightDir, normal);

	return (ambient +(1.0 - shadow) * (diffuse + specular));
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	float lightDistance = length(vec3(light.position) - fsIn.FragPos);
	float attenuation = 1.0/(light.constant + light.linear * lightDistance + light.quadratic * (lightDistance * lightDistance));
	
	vec3 lightDir = normalize(vec3(light.position) - fsIn.FragPos);

	float diffValue = max(dot(normal, lightDir),0.0);

	vec3 halfwayDir = normalize(lightDir + viewDir);
	float specValue = pow(max(dot(normal, halfwayDir),0.0), material.shininess);

	vec3 ambient = vec3(light.ambient) * vec3(texture(material.diffuse, fsIn.TexCoord));
	vec3 diffuse = vec3(light.diffuse) * diffValue  * vec3(texture(material.diffuse, fsIn.TexCoord));
	vec3 specular = vec3(light.specular) * specValue * vec3(texture(material.specular, fsIn.TexCoord));
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	float shadow = ShadowCalculation(fsIn.FragPosLightSpace, lightDir, normal);

	return (ambient + (1.0 - shadow) * (diffuse + specular));
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fsIn.FragPos);

	float theta = dot(lightDir,normalize(-light.direction));

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, fsIn.TexCoord));

	if(theta > light.cutOff)
	{
		float diffValue = max(dot(normal, lightDir),0.0);

		vec3 halfwayDir = normalize(lightDir + viewDir);
		float specValue = pow(max(dot(normal, halfwayDir),0.0), material.shininess);

		vec3 diffuse = light.diffuse * diffValue  * vec3(texture(material.diffuse, fsIn.TexCoord));
		vec3 specular = light.specular * specValue * vec3(texture(material.specular, fsIn.TexCoord));

		float shadow = ShadowCalculation(fsIn.FragPosLightSpace,lightDir, normal);

		return (ambient + (1.0 - shadow) * (diffuse + specular));
	}
	else
		return ambient;
}