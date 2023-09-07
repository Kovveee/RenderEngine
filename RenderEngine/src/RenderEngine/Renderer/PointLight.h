#pragma once
#include "LightSource.h"

struct PointLightData
{
	glm::vec4 position;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;

	float constant;
	float linear;
	float quadratic;
};

class PointLight: public LightSource
{
public:
	PointLight(unsigned int lightId, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 position);
	~PointLight();
	void SetInShader(Shader* shader) override;
	void* GetData() override;

	const static unsigned int Size = 4 * sizeof(glm::vec4) + 3 * sizeof(float);

	static unsigned int Count;
private:
	PointLightData m_data;
	glm::vec3 m_position;
	float m_constant;
	float m_linear;
	float m_quadratic;
	
};

